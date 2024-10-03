/*
 * Appl.c
 *
 * Created: 02/04/2019 21:29:10
 *  Author: Ana Watanabe
 */ 

//-------------------------------------- Include Files ----------------------------------------------------------------
//#include "C_Types.h"    ainda não...
#include <avr/io.h> //definições do componente especificado
#include <util/delay.h> /*biblioteca para o uso das rotinas de
//_delay_ms() e _delay_us()*/
#include "..\Header\Appl.h"
#include "..\Header\Gpio.h"
//-------------------------------------- PUBLIC (Variables) -----------------------------------------------------------


//-------------------------------------- Defines, Enumerations ----------------------------------------------------------------
#define ACESO       0
#define APAGADO     1
//-------------------------------------- Global Variables ----------------------------------------------------------------

unsigned char Timer_Counter;
unsigned char Toggle;
unsigned char Trigger;
//-------------------------------------- PRIVATE (Function Prototypes) ---------------------------------------------------


//=====================================================================================================================
//-------------------------------------- Public Functions -------------------------------------------------------------
//=====================================================================================================================


void Appl__Initialize(void)
{
// Chamar o Gpio_PinConfig() para configurar as saidas e entradas digitais

// apaga todos os leds


}


void Appl__Handler(void)
{
unsigned char value1, value2, value3;

// Ler as chaves pelo Gpio_PinRead() e acender o leds 
// pelo Gpio_PinWrite().


}