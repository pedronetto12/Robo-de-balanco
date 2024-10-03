#include <avr/io.h>
#include <avr/interrupt.h>
#include "..\H\variaveis.h"
#include "..\H\interrupcao.h"

//funções

ISR(TIMER1_COMPA_vect){ //temporizador
		micros++; //(us)
}


ISR(TIMER2_COMPA_vect){ //motores
	//Calculo de pulso para motor esquerdo
	contador_acelerador_motor_left ++;
	if(contador_acelerador_motor_left > acelerador_motor_left_memory){
		contador_acelerador_motor_left = 0;
		acelerador_motor_left_memory = acelerador_motor_left;
		if(acelerador_motor_left_memory < 0){
			PORTD &= 0b11110111;
			acelerador_motor_left_memory *= -1;
		}
		else PORTD |= 0b00001000;
	}
	else if(contador_acelerador_motor_left == 1)PORTD |= 0b00000100;
	else if(contador_acelerador_motor_left == 2)PORTD &= 0b11111011;
	
	//Calculo de pulso para motor direito
	contador_acelerador_motor_right++;
	if(contador_acelerador_motor_right > acelerador_motor_right_memory){
		contador_acelerador_motor_right = 0;
		acelerador_motor_right_memory = acelerador_motor_right;
		if(acelerador_motor_right_memory < 0){
			PORTD |= 0b00100000;
			acelerador_motor_right_memory *= -1;
		}
		else PORTD &= 0b11011111;
	}
	else if(contador_acelerador_motor_right == 1)PORTD |= 0b00010000;
	else if(contador_acelerador_motor_right == 2)PORTD &= 0b11101111;
}

	
void Reg_temp_Step(){
	TCCR2A = 0; //TCCR2A esteja definido como zero
	TCCR2B = 0; //TCCR2B esteja definido como zero
	TCCR2A |= (1 << WGM21); //CTC
	TCCR2B |= (1 << CS21); // prescaler para 8
	TIMSK2 |= (1 << OCIE2A); //Set bit de interrupção OCIE2A no registro TIMSK2
	//O registro de comparação é definido como 39 => 20us / (1s / (16.000.000MHz / 8))
	OCR2A = 39;

}
	
void Reg_temp_prog(){
	TCCR1A = 0; //TCCR1A esteja definido como zero
	TCCR1B = 0; //TCCR1B esteja definido como zero
	TCCR1B |= (1 << CS10)|(1 << WGM12); // prescaler para 1 e ativa modo ctc com TOP=OCR1A
	TIMSK1 |= (1 << OCIE1A); //Set bit de interrupção OCIE1A no registro TIMSK1
	//O registro de comparação é definido como 15 => 1us / (1s / (16.000.000MHz / 1)) - 1
	OCR1A = 15;
}
