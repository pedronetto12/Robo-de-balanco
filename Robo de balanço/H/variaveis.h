/*
 * variaveis.h
 *
 * Created: 26/07/2022 20:52:40
 *  Author: Máquina
 */ 


#ifndef VARIAVEIS_H_
#define VARIAVEIS_H_

#pragma once

//--- Variaveis ---//
#define address_mod_write  0b01101000 //endereço do modulo MPU-6050 (acelerometro)
#define address_mod_read  0b01101001
//OBS: com address R~W em 0, para escrita.

#define acc_calibration_value  1000 //Calibração do acelerometro
#define pid_p_ganho  18 //Configuração de ganho em P
#define pid_i_ganho  2.7 //Configuração de ganho em I
#define pid_d_ganho  0.01 //Configuração de ganho em D
#define turning_speed  20 //Ganho de velocidade
#define max_target_speed  100 //Velocidade Max

uint8_t start;

int left_motor, acelerador_motor_left, contador_acelerador_motor_left, acelerador_motor_left_memory;

int right_motor, acelerador_motor_right, contador_acelerador_motor_right,acelerador_motor_right_memory;

int giro_pitch_data_raw, giro_yaw_data_raw, acelerometro_data_raw;

long giro_yaw_calibracao_valor, giro_pitch_calibracao_valor;

int cont;

unsigned long loop_timer, micros;

float angle_gyro, angle_acc, angle, self_balance_pid_setpoint;

float pid_error_temp, pid_i_mem, pid_setpoint, giro_input, pid_output, pid_last_d_error;

float pid_output_left, pid_output_right;




#endif /* VARIAVEIS_H_ */