/*
 * interrupcao.h
 *
 * Created: 26/07/2022 21:50:01
 *  Author: Máquina
 */ 


#ifndef INTERRUPCAO_H_
#define INTERRUPCAO_H_
#pragma once
//prototipos
void Reg_temp_step();
void Reg_temp_prog();
ISR(TIMER2_COMPA_vect);
ISR(TIMER1_COMPA_vect);




#endif /* INTERRUPCAO_H_ */