#include "main.h"
#include "string.h"


extern QueueHandle_t xUsart2TxQueue;
extern QueueHandle_t xUsart2RxQueue;
extern TimerHandle_t xTimer1;
extern SemaphoreHandle_t sempHand;
extern MessageBufferHandle_t xRx2MessageBuffer;
extern QueueHandle_t MessageQueue;

uint8_t usar2_data_cnt = 0;
uint8_t usar1_data_cnt = 0;
extern char usa2_RX_buf[50]; 
extern char usa1_RX_buf[50]; 
char usar2_data;
char usar1_data;

size_t mesagebufret;
int main(){
	SystemInit();
	inits();
	portENABLE_INTERRUPTS();
	xUsart2TxQueue = xQueueCreate(10, sizeof(char*)*QUEBUFFERLENGTH);
	xTimer1 = xTimerCreate( " timer.1",se_DELAY_MS(2500),pdTRUE,NULL,Timer1_CallBack);
	sempHand = xSemaphoreCreateBinary();
	
	xRx2MessageBuffer = xMessageBufferCreate(20);
	MessageQueue = xQueueCreate(10,50);
	
	xTaskCreate ( vPeriodiktoggle12, "periodik toggle 12",1000,(void *)1000,4,NULL );
//	xTaskCreate ( vPeriodiktoggle13, "periodik toggle 13",1000,(void *)500,3,NULL );
//	xTaskCreate ( vPeriodiktoggle14, "periodik toggle 14",1000,(void *)250,2,NULL );
	xTaskCreate ( vPeriodiktoggle15, "periodik toggle 15",1000,(void *)4000,1,NULL );
	xTaskCreate ( MessageToQueue, "MessageToQueue", 2000, NULL, 2,NULL);
//	xTaskCreate( process_usart2, "uasrt_process",1000, NULL, 2,NULL);
	xTaskCreate( process_MessageQueue, "QUEUE_process",1000, NULL, 3,NULL);
	
	xTimerStart ( xTimer1, 0);
	xTaskCreate( vSe_Que_Receive, "que_receive",1000, NULL,2,NULL);
	vTaskStartScheduler();
	for(;;);

}

void USART2_IRQHandler(void)
{
	BaseType_t pxhigherpriorityTaskWoken;
	
	pxhigherpriorityTaskWoken = pdFALSE;
	//here we will check the data incoming or going
	//Receiving the data
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET)
	{
		//To receive data and locate them into our char variable.
		usar2_data= USART_ReceiveData(USART2);
		
		if ( usar2_data == 10 || usar2_data == 13  )
		{
					usa2_RX_buf[ usar2_data_cnt] = '\0';
			mesagebufret = xMessageBufferSendFromISR( xRx2MessageBuffer, usa2_RX_buf, strlen(usa2_RX_buf), &pxhigherpriorityTaskWoken);
			usar2_data_cnt	 = 0;

			#if USE_SEMAP
			xSemaphoreGiveFromISR ( sempHand, &pxhigherpriorityTaskWoken);
			#endif
		}
		else 
		{
			usa2_RX_buf[ usar2_data_cnt++ ] = USART_ReceiveData( USART2 );
		}
	}

	//Sending the data
	if (USART_GetITStatus(USART2, USART_IT_TXE) == SET)
	{
		USART_SendData(USART2, usa2_RX_buf[usar2_data_cnt ++]);
	}
	portYIELD_FROM_ISR( pxhigherpriorityTaskWoken );
}

void EXTI0_IRQHandler(){
	if(EXTI_GetITStatus(EXTI_Line0)!=RESET){   

		__NOP();	
			EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

void USART1_IRQHandler(void)
{
	//in here we will check the data incoming or going
	//Receiving the data
	if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{

		//To receive data and locate them into our char variable.
		usar1_data= USART_ReceiveData(USART1);
		
		if ( usar1_data == 10 || usar1_data == 13  ){
		
		}else {
		usa1_RX_buf[usar1_data_cnt++] = USART_ReceiveData(USART1);

		}
	}

	//Sending the data
	if (USART_GetITStatus(USART1, USART_IT_TXE) == SET)
	{
		USART_SendData(USART1, usa1_RX_buf[usar1_data_cnt ++]);
	}
}
