#define F_CPU 16000000 //frequancia do cristal externo do arduino uno 16MHz
#include <avr/io.h>
#include <avr/interrupt.h>
#include "..\H\i2c.h"
#include "..\H\variaveis.h"
#include "..\H\interrupcao.h"
#include "..\H\mat.h"
#include "..\H\mpu.h"


int main() {
	//inicialização
	I2C_Init();
	Reg_temp_Step();
	Reg_temp_prog();
	sei();  //habilita interrupção
	offset();
	DDRD = 0b00111100; //PIN 2,3,4,5 OUT
	calibracao();
	
	loop_timer = micros + 4000;//tempo de execução + 4ms
	while(1){ // loop
		calc_ang();
		start_condition();
		calc_giro();
		pid();
		tombo();
		motores();
		while(loop_timer > micros); //espera completar 4ms
		loop_timer += 4000; //adiciona + 4ms para proximo loop
	}
	return 0;
}

