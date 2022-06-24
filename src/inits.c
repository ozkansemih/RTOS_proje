
#include "inits.h"


void inits( void ){
	clock_config();
	init_rcc();
	init_gpioa();
//	init_Usart1();
//	init_Usart2();
	 init_Usart2();
	init_Usart1();

}
	
	
	

void init_rcc(){
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
}

void init_Usart1( void){

//	GPIO_InitTypeDef gp;
//	gp.GPIO_Mode = GPIO_Mode_AF;
//	gp.GPIO_Pin = GPIO_Pin_9;
////	gp.GPIO_OType = GPIO_OType;
////	gp.GPIO_PuPd = GPIO_PuPd_UP;
//		gp.GPIO_OType=GPIO_OType_OD;
//	gp.GPIO_PuPd=GPIO_PuPd_NOPULL;
//	gp.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA,&gp);
//	
//	USART_InitTypeDef usa;
//		GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);

//	usa.USART_BaudRate = 9600;
//	usa.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	usa.USART_Parity = USART_Parity_No;
//	usa.USART_StopBits = USART_StopBits_1;
//	usa.USART_WordLength = USART_WordLength_8b;
//	usa.USART_Mode = USART_Mode_Tx ;
//	USART_Init( USART1, &usa);
////	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
//	USART_Cmd(USART1,ENABLE);
			//GPIO and USART global structures 
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	//USART2 is connected to APB1 Periph Clock Bus and we enabled it.
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//GPIOA is connected to AHB1 Periph Clock Bus and we enabled it.
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		//Configuration of the GPIO pin for communication
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; //This is important. We will this pin except of INPUT, OUTPUT and ANALOG so we set as Alternate Function
	GPIO_InitStructure.GPIO_Pin   =  GPIO_Pin_7;   //Communicate on PA2 and PA3
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//We set the pin as Push Pull
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP; //And Pull Up. Keep it always on HIGH
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz; //And pin frequency
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//When we set a pin as Alternate Function, we need to specify what function do we use for, here we specified it as USART 2
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
		
	USART_InitStructure.USART_BaudRate 	              = 9600; //Set the baudrate. Hw many datas will be sent in a second.
	USART_InitStructure.USART_HardwareFlowControl     = USART_HardwareFlowControl_None;  //Do not check the data transmitted 
	USART_InitStructure.USART_Mode                    = USART_Mode_Rx;//Data tansmission modes
	USART_InitStructure.USART_Parity                  = USART_Parity_No; // USART parity settings
	USART_InitStructure.USART_StopBits                = USART_StopBits_1; //Set the stop bits
	USART_InitStructure.USART_WordLength              = USART_WordLength_8b;  //we will send the 8bit data
	USART_Init(USART1, &USART_InitStructure);   //and started the this configuration

	USART_Cmd(USART1, ENABLE); //USART is activated and ready to use
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
		NVIC_InitTypeDef NVIC_InitStructure; //NVIC structure variable
  
  	/* Enable the USARTx Interrupt */
  	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn; // We will use this channel to use USART2 NVIC
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4; //set the this NVIC priority
 	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
 	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ENABLE the NVIC
 	 NVIC_Init(&NVIC_InitStructure); //And submit the NVIC with USART2
		NVIC_SetPriority(USART1_IRQn, 11); 

	USART_Cmd(USART1, ENABLE); //USART is activated and ready to use
	
	
}

void init_Usart2( void){

//	GPIO_InitTypeDef gp;
//	gp.GPIO_Mode = GPIO_Mode_AF;
//	gp.GPIO_Pin = GPIO_Pin_2;
////	gp.GPIO_OType = GPIO_OType;
////	gp.GPIO_PuPd = GPIO_PuPd_UP;
//		gp.GPIO_OType=GPIO_OType_OD;
//	gp.GPIO_PuPd=GPIO_PuPd_NOPULL;
//	gp.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA,&gp);
//	
//	USART_InitTypeDef usa;
//		GPIO_PinAFConfig(GPIOA,GPIO_PinSource2,GPIO_AF_USART2);

//	usa.USART_BaudRate = 9600;
//	usa.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	usa.USART_Parity = USART_Parity_No;
//	usa.USART_StopBits = USART_StopBits_1;
//	usa.USART_WordLength = USART_WordLength_8b;
//	usa.USART_Mode = USART_Mode_Tx ;
//	USART_Init( USART2, &usa);
////	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
//	USART_Cmd(USART2,ENABLE);


		//GPIO and USART global structures 
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	//USART2 is connected to APB1 Periph Clock Bus and we enabled it.
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	//GPIOA is connected to AHB1 Periph Clock Bus and we enabled it.
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	//Configuration of the GPIO pin for communication
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF; //This is important. We will this pin except of INPUT, OUTPUT and ANALOG so we set as Alternate Function
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_2 | GPIO_Pin_3;   //Communicate on PA2 and PA3
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//We set the pin as Push Pull
	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP; //And Pull Up. Keep it always on HIGH
	GPIO_InitStructure.GPIO_Speed	= GPIO_Speed_50MHz; //And pin frequency
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//When we set a pin as Alternate Function, we need to specify what function do we use for, here we specified it as USART 2
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	
	
	USART_InitStructure.USART_BaudRate 	              = 9600; //Set the baudrate. Hw many datas will be sent in a second.
	USART_InitStructure.USART_HardwareFlowControl     = USART_HardwareFlowControl_None;  //Do not check the data transmitted 
	USART_InitStructure.USART_Mode                    = USART_Mode_Tx | USART_Mode_Rx;//Data tansmission modes
	USART_InitStructure.USART_Parity                  = USART_Parity_No; // USART parity settings
	USART_InitStructure.USART_StopBits                = USART_StopBits_1; //Set the stop bits
	USART_InitStructure.USART_WordLength              = USART_WordLength_8b;  //we will send the 8bit data
	USART_Init(USART2, &USART_InitStructure);   //and started the this configuration

	USART_Cmd(USART2, ENABLE); //USART is activated and ready to use

USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);

NVIC_InitTypeDef NVIC_InitStructure; //NVIC structure variable
  	/* Enable the USARTx Interrupt */
  	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn; // We will use this channel to use USART2 NVIC
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 4; //set the this NVIC priority
 	 NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
 	 NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //ENABLE the NVIC
 	 NVIC_Init(&NVIC_InitStructure); //And submit the NVIC with USART2
	NVIC_SetPriority(USART2_IRQn, 11); 

	USART_Cmd(USART2, ENABLE); //USART is activated and ready to use
	
	
}
		void USART_Puts(USART_TypeDef* USARTx, volatile char	 *data){
		while(*data){
		while(!(USARTx->SR & 0x00000040));
		USART_SendData(USARTx, *data);
			data++;
		}
	}


	
void init_gpioa(){
	EXTI_InitTypeDef EXTI_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	GPIO_InitTypeDef gp;
	gp.GPIO_Pin= GPIO_Pin_12 |GPIO_Pin_13 |GPIO_Pin_14 |GPIO_Pin_15;
	gp.GPIO_Mode = GPIO_Mode_OUT;
	gp.GPIO_OType= GPIO_OType_PP;
	gp.GPIO_PuPd= GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD,&gp);
	
	gp.GPIO_Pin = GPIO_Pin_0;
	gp.GPIO_Mode = GPIO_Mode_IN;
	gp.GPIO_PuPd = GPIO_PuPd_DOWN;
	gp.GPIO_OType = GPIO_OType_PP;
	gp.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &gp);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}

void clock_config(){
	SystemCoreClockUpdate();
	if(SysTick_Config(SystemCoreClock/1000)){
		while(1);
	}
}
