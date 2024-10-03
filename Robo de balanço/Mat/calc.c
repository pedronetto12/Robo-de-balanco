#include <avr/io.h>
#include "../H/i2c.h"
#include "..\H\variaveis.h"
#include "..\H\mat.h"


void calc_ang(){//Calculo de Angulo
	I2C_Start(); //Condição de START
	I2C_Write(address_mod_write); //Endereço do slave + RW = 0
	I2C_Write(0x3F); //Registrador ACCEL_ZOUT_H
	I2C_Start(); //Condição de RE-START
	I2C_Write(address_mod_read); //Endereço do slave + RW = 1
	//Combine os dois bytes de 0x3F e 0x40 (ACCEL_ZOUT[15:8] + ACCEL_ZOUT[7:0])
	acelerometro_data_raw = I2C_Read(1)<<8 |I2C_Read(0);
	I2C_Stop();
		
	acelerometro_data_raw += acc_calibration_value; //Adiciona valor de calibração
	if(acelerometro_data_raw > 8200)acelerometro_data_raw = 8200;
	if(acelerometro_data_raw < -8200)acelerometro_data_raw = -8200; //Limita em +/-8200;
		
	//Calcula o valor do angulo de acordo com o modulo
	angle_acc = asin((float)acelerometro_data_raw/8200.0)* 63.14;
}

void start_condition(){
	//Robo só funcionará quando chegar nesse range de angulação
	if(start == 0 && angle_acc > -0.5&& angle_acc < 0.5){
		angle_gyro = angle_acc;
		start = 1;
	}
}

void calc_giro(){	
	I2C_Start(); //Condição de START
	I2C_Write(address_mod_write); //Endereço do slave + RW = 0
	I2C_Write(0x43); //Registrador GYRO_XOUT_H
	I2C_Start(); //Condição de RE-START
	I2C_Write(address_mod_read); //Endereço do slave + RW = 1
	//Combine os dois bytes de 0x43 e 0x44 (GYRO_XOUT[15:8]+GYRO_XOUT[7:0])
	giro_yaw_calibracao_valor += I2C_Read(1)<<8 |I2C_Read(1);
	//Combine os dois bytes de 0x45 e 0x46 (GYRO_YOUT[15:8]+GYRO_YOUT[7:0])
	giro_pitch_calibracao_valor += I2C_Read(1)<<8 |I2C_Read(0);
	I2C_Stop();
		
	//Adiciona valor medio de calibração calculado na função GIRO_offset
	giro_pitch_data_raw -= giro_pitch_calibracao_valor;
	//Calcula o percorrido durante este ângulo de loop e adiciona isso à variável angle_gyro
	angle_gyro += giro_pitch_data_raw * 0.000031;

	//MPU-6050 offset para compensação
	//Adiciona valor medio de calibração calculado na função GIRO_offset
	giro_yaw_data_raw -= giro_yaw_calibracao_valor;
	//Corrige o desvio do ângulo do giroscópio com o ângulo do acelerômetro
	angle_gyro = angle_gyro * 0.9996 + angle_acc * 0.0004;
}


void pid(){//PID calculo do controlador
	pid_error_temp = angle_gyro - self_balance_pid_setpoint - pid_setpoint;
	if(pid_output > 10 || pid_output < -10)pid_error_temp += pid_output * 0.015;
	//Calcule o valor do controlador I e adicione-o à variável pid_i_mem
	pid_i_mem += pid_i_ganho * pid_error_temp;
	if(pid_i_mem > 400)pid_i_mem = 400; //Limita o controlador
	else if(pid_i_mem < -400)pid_i_mem = -400;
	//Calcula a saída do controlador PID
	pid_output = pid_p_ganho * pid_error_temp + pid_i_mem + pid_d_ganho * (pid_error_temp -
	pid_last_d_error);
	if(pid_output > 400)pid_output = 400; //Limita o controlador
	else if(pid_output < -400)pid_output = -400;
	pid_last_d_error = pid_error_temp; //Armazenar o erro para o próximo loop
			
	//Cria uma banda morta afim de parar os motores quando o robô estiver balanceado
	if(pid_output < 5 && pid_output > -5)pid_output = 0;
}

void tombo(){
	//Desliga o robô se ele tombar ou a variável de partida for zero
	if(angle_gyro > 30 || angle_gyro < -30 || start == 0){
		pid_output = 0;
		pid_i_mem = 0;
		start = 0;
		self_balance_pid_setpoint = 0;
	}
}

void motores(){
	////////////////////////////////////////////////////////////////////////////////////////
	//Balanço e controle dos motores
	////////////////////////////////////////////////////////////////////////////////////////
	pid_output_left = pid_output; // variavel para controle do motor esquerdo
	pid_output_right = pid_output; // variavel para controle do motor direito

	if(pid_setpoint == 0){ //Se o ponto de ajuste for zero graus
		//Aumente a variavel self_balance_pid_set do robô ainda está se movendo para frente
		if(pid_output < 0)self_balance_pid_setpoint += 0.0015;
		//Diminui a variavel self_balance_pid_set do robô ainda está se movendo para tras.
		if(pid_output > 0)self_balance_pid_setpoint -= 0.0015;
	}
	//--- Transformação de grafico linear para logaritmico ---//
	if(pid_output_left > 0)pid_output_left = 405 - (1/(pid_output_left + 9)) * 5500;
	else if(pid_output_left < 0)pid_output_left = -405 - (1/(pid_output_left - 9)) * 5500;
	if(pid_output_right > 0)pid_output_right = 405 - (1/(pid_output_right + 9)) * 5500;
	else if(pid_output_right < 0)pid_output_right = -405 - (1/(pid_output_right - 9)) *
	5500;
	//---Calcula o tempo de pulso necessário para ambos os motores (esquerdo e direito)---//
	if(pid_output_left > 0)left_motor = 400 - pid_output_left;
	else if(pid_output_left < 0)left_motor = -400 - pid_output_left;
	else left_motor = 0;
	if(pid_output_right > 0)right_motor = 400 - pid_output_right;
	else if(pid_output_right < 0)right_motor = -400 - pid_output_right;
	else right_motor = 0;
	//--- Copiar valores calculados para as variaveis da rotina de interrupção ---//
	acelerador_motor_left = left_motor;
	acelerador_motor_right = right_motor;
	
}