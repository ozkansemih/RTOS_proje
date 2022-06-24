#ifndef _SE_TASK_H_
#define _SE_TASK_H_

	#include "FreeRTOS.h"
	
	#include "task.h"
	#include "timers.h"
	#include "queue.h"
	#include "semphr.h"
	#include "stream_buffer.h"
	#include "message_buffer.h"


	#include "defines.h"
	#include "inits.h"
	#include "leds.h"

	void vPeriodiktoggle12( void * param );
	void vPeriodiktoggle13( void * param );
	void vPeriodiktoggle14( void * param );
	void vPeriodiktoggle15( void * param );
	void Timer1_CallBack( TimerHandle_t timer );
	void put_tickstamp(char* str);
	void vSe_Que_Receive( void * param);
	void MessageToQueue( void *param);
	void process_MessageQueue( void *param);
	void process_usart2(void * param);
	void fnc_sendUSART(USART_TypeDef *USARTx, volatile char *s) ;
	
	void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName );
	void vApplicationIdleHook( void );
	void vApplicationTickHook( void );
	void vApplicationMallocFailedHook( void );
#endif
