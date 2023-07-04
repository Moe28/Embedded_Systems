/*
 * MEXTI.c
 *
 *  Created on: 29 Jun 2023
 *      Author: Boufa
 */




#include "inc/MEXTI.h"




#define EXTI_BASE			0x40010400UL





typedef struct{

	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;

}EXTI_t;

  volatile EXTI_t * const EXTI_Ptr     = 		(volatile EXTI_t * const) EXTI_BASE;

/********************************
 *
 *Generic Variables
 * ************************************/
void (*GP_IRQCallBack[15])(void);
/********************************
 *
 *Generic Macros
 * ************************************/


#define AFIO_GPIO_EXTI_Mapping(x)	(	(x== GPIOA_Ptr)?	0 :\
										(x==GPIOB_Ptr)?	1 :0
										//(x==GPIOC_Ptr)?	2 :0 )




/********************************
 *
 *Static Function
 * ************************************/
void Enable_NVIC(uint16_t IRQ_Number){
	switch (IRQ_Number)
	{
				case 0 : NVIC_IRQ6_EXT0_Enable; break;
				case 1 : NVIC_IRQ7_EXT1_Enable; break;
				case 2 : NVIC_IRQ8_EXT2_Enable;break;
				case 3 : NVIC_IRQ9_EXT3_Enable; break;
				case 4 : NVIC_IRQ10_EXT4_Enable; break;
				case 5:
				case 6:
				case 7 :
				case 8 :
				case 9 :NVIC_IRQ23_EXT5_9_Enable;break;
				case 10:
				case 11:
				case 12 :
				case 13:
				case 14 :
				case 15:NVIC_IRQ40_EXT10_15_Enable; break;

	}
}
void Disable_NVIC (uint16_t IRQ_Number)
{
	switch (IRQ_Number)
		{
					case 0 : NVIC_IRQ6_EXT0_Disable; break;
					case 1 : NVIC_IRQ7_EXT1_Disable; break;
					case 2 : NVIC_IRQ8_EXT2_Disable;break;
					case 3 : NVIC_IRQ9_EXT3_Disable; break;
					case 4 : NVIC_IRQ10_EXT4_Disable; break;
					case 5:
					case 6:
					case 7 :
					case 8 :
					case 9 :NVIC_IRQ23_EXT5_9_Disable;break;
					case 10:
					case 11:
					case 12 :
					case 13:
					case 14 :
					case 15:NVIC_IRQ40_EXT10_15_Disable; break;

		}
}




void Update_EXTI( EXTI_Pinconfig_t* EXTI_Pin){


	//1- Configure GPIO to be AF Input -> Floating INPUT
		GPIO_Pin_config_t PinConfig;
		PinConfig.GPIO_Pin =  EXTI_Pin->EXTIPin.GPIO_PIN;
		PinConfig.GPIO_Mode = GPIO_Mode_Input_FLO;
	 	GPIO_Init(EXTI_Pin->EXTIPin.GPIO_Port, &PinConfig);
	//===============================================================//
		//2- UPDATE AFIO to Route between EXTI Line with PORT A,B,C
		uint8_t  AFIO_EXTICR_index = EXTI_Pin->EXTIPin.EXTI_Line / 4 ;

		uint8_t	AFIO_EXTICR_Postion = (EXTI_Pin->EXTIPin.EXTI_Line % 4) * 4 ;
		uint32_t	tempreg =AFIO_Ptr->EVCEXTICR[AFIO_EXTICR_index];

	//Clear the Four Bit

		tempreg &= ~(0xF<<AFIO_EXTICR_Postion);

		tempreg |= (AFIO_GPIO_EXTI_Mapping(EXTI_Pin->EXTIPin.GPIO_Port)&0xF) << AFIO_EXTICR_Postion);
		AFIO_Ptr->EVCEXTICR[AFIO_EXTICR_index]= tempreg ;

		//===============================================================//
		//3-Update Rising and Falling Edge

		EXTI_Ptr->RTSR &= ~(1<<EXTI_Pin->EXTIPin.EXTI_Line) ;
		EXTI_Ptr->FTSR &= ~(1<<EXTI_Pin->EXTIPin.EXTI_Line) ;

		if (EXTI_Pin->Trigger_Case == EXTI_Falling)
		{
			EXTI_Ptr->FTSR |= (1<<EXTI_Pin->EXTIPin.EXTI_Line) ;

		}
		else if (EXTI_Pin->Trigger_Case == EXTI_Rising)
		{
			EXTI_Ptr->RTSR |= (1<<EXTI_Pin->EXTIPin.EXTI_Line) ;

		}
		else {
			EXTI_Ptr->FTSR |= (1<<EXTI_Pin->EXTIPin.EXTI_Line) ;
			EXTI_Ptr->RTSR |= (1<<EXTI_Pin->EXTIPin.EXTI_Line) ;
		}
		//===============================================================//
		//4-Update Interrupt Handling Call Back
		GP_IRQCallBack[EXTI_Pin->EXTIPin.EXTI_Line] = EXTI_Pin->Ptr_IRQ_CallBack;

		//===============================================================//
		//5-Enable or Disable IRQ  and NVIC

		if(EXTI_Pin->IRQ_EN == EXTI_IRQ_Enable){
			EXTI_Ptr->IMR |= (1<< (EXTI_Pin->EXTIPin.EXTI_Line));
			Enable_NVIC(EXTI_Pin->EXTIPin.EXTI_Line);
		}
		else if (EXTI_Pin->IRQ_EN == EXTI_IRQ_Disable){
			EXTI_Ptr->IMR &= ~(1<< (EXTI_Pin->EXTIPin.EXTI_Line));
			Disable_NVIC(EXTI_Pin->EXTIPin.EXTI_Line);
		}
}







/********************************
 *
 * API Implementation
 * ************************************/

/**================================================================
* @Fn						-ExtInit
 * @brief 					-this is used to inialize EXTI from SpecifiC GPIO PIN and specify the Mask/Trigger Condition and IRQ CallBack
* @param [in] 				-priority_grouping: Enumerate Groups & sub groups
* @retval 					-none
* Note						-none
*/

void Ext_GPIO_Init(EXTI_Pinconfig_t* EXTI_Pin){


	Update_EXTI(EXTI_Pin);


}

/**================================================================
* @Fn						-Ext_GPIO_DeInit
 * @brief 					-this is used to DeIntialize and Reset  EXTI Registers
* @param [in] 				-Void
* @retval 					-none
* Note						-none
*/
void Ext_GPIO_DeInit(void){

	EXTI_Ptr->EMR= 0x00000000;
	EXTI_Ptr->FTSR= 0x00000000;
	EXTI_Ptr->IMR= 0x00000000;
	EXTI_Ptr->PR= 0xFFFFFFFF;
	EXTI_Ptr->RTSR= 0x00000000;
	EXTI_Ptr->SWIER= 0x00000000;


	// DISABle all External Interrupts for NVIC

	NVIC_IRQ6_EXT0_Disable;
	NVIC_IRQ7_EXT1_Disable;
	NVIC_IRQ8_EXT2_Disable;
	NVIC_IRQ9_EXT3_Disable;
	NVIC_IRQ10_EXT4_Disable;
	NVIC_IRQ23_EXT5_9_Disable;
	NVIC_IRQ40_EXT10_15_Disable;

}

/**================================================================
* @Fn						-Ext_GPIO_Update
 * @brief 					-this is used to DeIntialize and Reset  EXTI pin, and return the port to its reset value
* @param [in] 				-Void
* @retval 					-none
* Note						-none
*/
void Ext_GPIO_Update(EXTI_Pinconfig_t* EXTI_Pin){

	Update_EXTI(EXTI_Pin);
}



/***************************
 * ISR FunctionS
 * ****************************/

void EXTI0_IRQHandler(void){
// Clear pending register

	EXTI_Ptr->PR  |= (1<<0);
	GP_IRQCallBack[0]();
}
void EXTI1_IRQHandler(void){
	EXTI_Ptr->PR  |= (1<<1);
	GP_IRQCallBack[1]();

}
void EXTI2_IRQHandler(void){
	EXTI_Ptr->PR  |= (1<<2);
	GP_IRQCallBack[2]();

}
void EXTI3_IRQHandler(void){
	EXTI_Ptr->PR  |= (1<<3);
	GP_IRQCallBack[3]();

}
void EXTI4_IRQHandler(void){
	EXTI_Ptr->PR  |= (1<<4);
	GP_IRQCallBack[4]();

}
void EXTI9_5_IRQHandler(void){

	if (EXTI_Ptr->PR & 1<<5){EXTI_Ptr->PR  |= (1<<5); 	GP_IRQCallBack[5]();}
	if (EXTI_Ptr->PR & 1<<6){EXTI_Ptr->PR  |= (1<<6); 	GP_IRQCallBack[6]();}
	if (EXTI_Ptr->PR & 1<<7){EXTI_Ptr->PR  |= (1<<7); 	GP_IRQCallBack[7]();}
	if (EXTI_Ptr->PR & 1<<8){EXTI_Ptr->PR  |= (1<<8); 	GP_IRQCallBack[8]();}
	if (EXTI_Ptr->PR & 1<<9){EXTI_Ptr->PR  |= (1<<9); 	GP_IRQCallBack[9]();}

}


void EXTI15_10_IRQHandler(void){
		if (EXTI_Ptr->PR & 1<<10){EXTI_Ptr->PR  |= (1<<10); 	GP_IRQCallBack[10]();}
		if (EXTI_Ptr->PR & 1<<11){EXTI_Ptr->PR  |= (1<<11); 	GP_IRQCallBack[11]();}
		if (EXTI_Ptr->PR & 1<<12){EXTI_Ptr->PR  |= (1<<12); 	GP_IRQCallBack[12]();}
		if (EXTI_Ptr->PR & 1<<13){EXTI_Ptr->PR  |= (1<<13); 	GP_IRQCallBack[13]();}
		if (EXTI_Ptr->PR & 1<<14){EXTI_Ptr->PR  |= (1<<14); 	GP_IRQCallBack[14]();}
		if (EXTI_Ptr->PR & 1<<15){EXTI_Ptr->PR  |= (1<<15); 	GP_IRQCallBack[15]();}

}


