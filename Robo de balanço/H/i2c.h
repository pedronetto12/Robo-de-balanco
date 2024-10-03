/*
 * i2c.h
 *
 * Created: 26/07/2022 21:49:43
 *  Author: Máquina
 */ 


#ifndef I2C_H_
#define I2C_H_

#pragma once
/***************************************************************************************************
                             Protótipos das funções
***************************************************************************************************/
void I2C_Init();
void I2C_Start();
void I2C_Stop(void);
void I2C_Write(uint8_t v_i2cData_u8);
uint8_t I2C_Read(uint8_t v_ackOption_u8);



#endif /* I2C_H_ */