#include <avr/io.h>
#include "..\H\variaveis.h"
#include "..\H\i2c.h"
#include "..\H\mpu.h"


	
//funções
void offset(){
	//Acordando modulo
	I2C_Start(address_mod_write); //Condição de START
	I2C_Write(address_mod_write); //Endereço do slave + RW = 0
	I2C_Write(0x6B); //Registrador PWR_MGMT_1
	I2C_Write(0x00); //Ativa o modulo
	I2C_Stop(); //Condição de STOP
	
	//Definir a escala total do giroscópio para +/- 250 °/s
	I2C_Start(); //Condição de START
	I2C_Write(address_mod_write); //Endereço do slave + RW = 0
	I2C_Write(0x1B); //Registrador GYRO_CONFIG
	I2C_Write(0x00); //Configura escala de giro = 250 °/s
	I2C_Stop(); //Condição de STOP
	
	//Definir a escala completa do acelerômetro para +/- 4g
	I2C_Start(); //Condição de START
	I2C_Write(address_mod_write); //Endereço do slave + RW = 0
	I2C_Write(0x1C); //Registrador ACCEL_CONFIG
	I2C_Write(0x08); //Configura escala de aceleração = 4g
	I2C_Stop(); //Condição de STOP
	
	//Definir alguma filtragem para melhorar os dados brutos
	I2C_Start(); //Condição de START
	I2C_Write(address_mod_write); //Endereço do slave + RW = 0
	I2C_Write(0x1A); //Registrador CONFIG
	I2C_Write(0x03); //Configura filtro passa-baixo digital para ~43Hz
	I2C_Stop(); //Condição de STOP
}

void calibracao(){
	for(int i = 0; i < 500; i++){
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
	}
	giro_yaw_calibracao_valor/=500;
	giro_pitch_calibracao_valor/=500;
}

