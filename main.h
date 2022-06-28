
#include "stm32f4xx.h"                  // Device header
#include "stm32f4xx_exti.h"             // Keil::Device:StdPeriph Drivers:EXTI
#include "stm32f4xx_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f4xx_sdio.h"             // Keil::Device:StdPeriph Drivers:SDIO
#include "stm32f4xx_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f4xx_syscfg.h"           // Keil::Device:StdPeriph Drivers:SYSCFG
#include "stm32f4xx_usart.h"            // Keil::Device:StdPeriph Drivers:USART
#include "misc.h"
#include "stm32f4xx_spi.h"              // Keil::Device:StdPeriph Drivers:SPI


#include "se_tasks.h"
#include "spi_drive.h"
#include "PCD8544.h"




void vApplicationMallocFailedHook( void );

