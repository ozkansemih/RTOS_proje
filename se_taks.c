	#include "string.h"
	#include "se_tasks.h"

	TickType_t timeperiod ;
	TickType_t curr_Tick ;
	
	QueueHandle_t xUsart2TxQueue;
	QueueHandle_t xUsart2RxQueue;
	
	MessageBufferHandle_t xRx2MessageBuffer;
	QueueHandle_t MessageQueue;

	TimerHandle_t xTimer1;
	BaseType_t que;
	UBaseType_t numbofIteminTxBuf;
	SemaphoreHandle_t sempHand;
	char usa2_RX_buf[50]; 
	char usa1_RX_buf[50];
	
	char  task12_buffer[QUEBUFFERLENGTH] ;
	char 	task13_buffer [QUEBUFFERLENGTH];
	char  task14_buffer[QUEBUFFERLENGTH] ;
	char  task15_buffer[QUEBUFFERLENGTH];
	char que_recev_buffer[QUEBUFFERLENGTH];
	char timer_str_buff[32]= "000000_TIMER_UP\r\n\0";
		
	void vPeriodiktoggle12(void * param){
		TickType_t xstartTick = xTaskGetTickCount();
		int tick_to_wait = (int ) param;
		strcpy(task12_buffer+6 ,"semih 12\r\n");
		char  task12_que_buffer[QUEBUFFERLENGTH] = "str_from_queue_12\r\n\0";

		for(;;){
			put_tickstamp(task12_buffer);
			led12_toggle();
			que = xQueueSendToBack(xUsart2TxQueue,task12_que_buffer,se_DELAY_MS(20));
			vTaskSuspendAll();
			fnc_sendUSART(USART2, task12_buffer);
			xTaskResumeAll();
			xTaskDelayUntil(&xstartTick, se_DELAY_MS( tick_to_wait) );
		}
	}

	void vPeriodiktoggle13(void * param){
		TickType_t xstartTick = xTaskGetTickCount();
		int tick_to_wait = (int ) param;
		strcpy(task13_buffer+6 ,"samet 13\r\n");
		char  task13_que_buffer[QUEBUFFERLENGTH] = "str_from_queue_13\r\n\0";

		for(;;){
			put_tickstamp(task13_buffer);
			led13_toggle();
			que = xQueueSendToBack( xUsart2TxQueue, task13_que_buffer, se_DELAY_MS(20));
			vTaskSuspendAll();
			fnc_sendUSART(USART2, task13_buffer);
			xTaskResumeAll();
			xTaskDelayUntil(&xstartTick, se_DELAY_MS( tick_to_wait) );
		}
	}
	
	void vPeriodiktoggle14(void * param){
		TickType_t xstartTick = xTaskGetTickCount();
		int tick_to_wait = (int ) param;
		strcpy(task14_buffer+6 ,"erol 14\r\n");
		char  task14_que_buffer[QUEBUFFERLENGTH] = "str_from_queue_14\r\n\0";

		for(;;){
			put_tickstamp(task14_buffer);
			led14_toggle();
			que = xQueueSendToBack( xUsart2TxQueue, task14_que_buffer, se_DELAY_MS(20));
			vTaskSuspendAll();
			fnc_sendUSART(USART2, task14_buffer);
			xTaskResumeAll();
			xTaskDelayUntil(&xstartTick, se_DELAY_MS( tick_to_wait) );
		}
	}
	
	void vPeriodiktoggle15(void * param){
		TickType_t xstartTick = xTaskGetTickCount();
		int tick_to_wait = (int ) param;
		strcpy(task15_buffer+6 ,"iko 15\r\n");
		char  task15_que_buffer[QUEBUFFERLENGTH] = "str_from_queue_15\r\n\0";

		for(;;){
			put_tickstamp(task15_buffer);
			led15_toggle();
			que = xQueueSendToBack( xUsart2TxQueue, task15_que_buffer, se_DELAY_MS(20));
			vTaskSuspendAll();
			fnc_sendUSART(USART2, task15_buffer);
			xTaskResumeAll();
			xTaskDelayUntil(&xstartTick, se_DELAY_MS( tick_to_wait )) ;
		}
	}

	void Timer1_CallBack( TimerHandle_t timer ){
		static int cnt;
		cnt++;
		put_tickstamp( timer_str_buff );
		
		fnc_sendUSART(USART2, timer_str_buff);
		timeperiod =xTimerGetPeriod(timer);
		xTimerChangePeriod( timer,xTimerGetPeriod(timer)*2,0);
		timeperiod =xTimerGetPeriod(timer);
		if(cnt == 4){
			__NOP();
		}
	}

	void put_tickstamp(char* str){
		curr_Tick = xTaskGetTickCount();
		
		str[5] ='0'+ curr_Tick/1 %10;
		str[4] ='0'+ curr_Tick/10 %10;
		str[3] ='0'+ curr_Tick/100 %10;
		str[2] ='0'+ curr_Tick/1000 %10;
		str[1] ='0'+ curr_Tick/10000 %10;
		str[0] ='0'+ curr_Tick/100000 %10;
	}

	void vSe_Que_Receive( void * param){
		TickType_t xTickTimeou = xTaskGetTickCount();
		for(;;){

			numbofIteminTxBuf = uxQueueMessagesWaiting( xUsart2TxQueue);
			BaseType_t ret= xQueueReceive( xUsart2TxQueue, que_recev_buffer,NULL );
				
			if( ret ==  pdPASS){
				vTaskSuspendAll();
				que_recev_buffer[0] = '0' + (numbofIteminTxBuf/100) % 10;
				que_recev_buffer[1] = '0' + (numbofIteminTxBuf/10) % 10;
				que_recev_buffer[2] = '0' + (numbofIteminTxBuf/1) % 10;

				fnc_sendUSART(USART2,que_recev_buffer);
				xTaskResumeAll();
			}
			xTaskDelayUntil( &xTickTimeou, se_DELAY_MS(20));
		}
	}
	
	void MessageToQueue( void *param){
				char str[32]="DEADBEEFdeadbeefDEADbeefdeadBEEF";
				size_t rec_data;
			for(;;){
				rec_data = xMessageBufferReceive( xRx2MessageBuffer, str, 50, portMAX_DELAY);
				str[rec_data] = 13;
				str[rec_data+1] = 10;
				xQueueSendToBack( MessageQueue, str, 0);

			}
	}
	
	void process_MessageQueue( void *param){
		char str[50];
		for(;;){
		
			xQueueReceive( MessageQueue, str, portMAX_DELAY);
			if ( !strncmp(str,"ready" ,5) ){
				fnc_sendUSART(USART2, "QUEUEmesazinizi aldim sayin basbakannim\0");
				__NOP();	
			}
			else	if ( !strncmp(str,"not ready", 9) ){
				fnc_sendUSART(USART2, "QUEUEmesazinizi yine aldim sayin basbakannim\0");
				__NOP();	
			} else{
				fnc_sendUSART(USART2, "QUEUEne yolladin sayin basbakannim\0");
				__NOP();	

			}
		}
	}

void process_usart2
	(void * param){
//char str[50];
			for(;;){
		//		xMessageBufferReceive( xRx2MessageBuffer, str, 50, portMAX_DELAY);
			#if USE_SEMAP 
				xSemaphoreTake( sempHand, portMAX_DELAY);
			#endif
				if ( !strncmp(usa2_RX_buf,"ready" ,5) ){
				fnc_sendUSART(USART2, "mesazinizi aldim sayin basbakannim\0");
				__NOP();	
			}
			else	if ( !strncmp(usa2_RX_buf,"not ready", 9) ){
				fnc_sendUSART(USART2, "mesazinizi yine aldim sayin basbakannim\0");
				__NOP();	
			} else{
				fnc_sendUSART(USART2, "ne yolladin sayin basbakannim\0");
				__NOP();	

			}
		}
	}

	void fnc_sendUSART(USART_TypeDef *USARTx, volatile char *s){
		while(*s) //do it for all characters
		{
			//Check the USASRT modul is avail, if we do not check our data will be disturbed
			while( !(USARTx ->SR & 0x00000040) ){}
			
			USART_SendData(USARTx, *s); //send a character
			*s++; //go the next character
			
		}
	}


	void vApplicationMallocFailedHook( void ){

	}


	void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName ){
		/* This function will only be called if a task overflows its stack.  Note
		that stack overflow checking does slow down the context switch
		implementation. */
		__NOP();
		for( ;; );
	}
	/*-----------------------------------------------------------*/

	void vApplicationIdleHook( void ){
		/* This example does not use the idle hook to perform any processing. */
		__NOP();
	}
	/*-----------------------------------------------------------*/

	void vApplicationTickHook( void ){
		/* This example does not use the tick hook to perform any processing. */
		__NOP();
	}

	void HardFault_Handler(){
		__NOP();
	}
