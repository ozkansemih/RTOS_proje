

#ifndef INITS_H
#define INITS_H

#include "stm32f4xx_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f4xx_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI
#include "stm32f4xx_usart.h"            // Keil::Device:StdPeriph Drivers:USART


void inits( void );
void init_rcc( void );
void init_gpioa( void );
void clock_config( void );
void init_Usart1( void );
void init_Usart2( void );
void delay( int ) ;
		

#endif
