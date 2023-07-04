/*
 * MGPIO.c
 *
 *  Created on: 29 Jun 2023
 *      Author: Boufa
 */




/***********************************
includes
* ************************************/
#include "inc/MGPIO.h"
/***********************************
Defines
************************************/

#define GPIOA_BASE 			0x40010800UL
#define GPIOB_BASE 			0x40010C00UL
#define GPIOC_BASE 			0x40011000UL



struct GPIO_reg {
	uint32_t CRL;
	uint32_t CRH;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t BRR;
	uint32_t LCKR;

};


	volatile GPIO_t * const GPIOA_Ptr 	 = 		(volatile GPIO_t * const )GPIOA_BASE;
	volatile GPIO_t * const GPIOB_Ptr 	 = 		(volatile GPIO_t * const )GPIOB_BASE;

/***********************************
 * Defines for ImplementationFunc
 * ************************************/









//static functions Prototypes
static uint8_t Get_CRLH_Position(uint16_t GPIO_Pin_Number);

/***************************************************
 * API's Implementation
 *
 * **************************************************/
/**================================================================
* @Fn						-GPIO_Init
* @brief 					- Intialize GPIO specific port and Specific Pin
* @param [in] 				-GPIOx: where Port could Be (A,B,..etc)
* @param [in] 				-GPIO_Pin_config_t : Specific Pin configuration
* @retval 					-none
* Note						-none
*/

void Enable_GPIOx (){
	RCC_GPIOA_CLK_EN();

}

void GPIO_Init(GPIO_t* GPIOx, GPIO_Pin_config_t* GPIO_Pin){
			/*check parameters, as:
			 * 1-Pin Number
			 * 2-GPIO Mode
			 * 3-GPIO PULL*/

	//CRL --> COnfigure Pins from  0>>7//
	//CRH --> Configure Pins from 8>>15//
	//  ternary operator to know which register based on the pins//

volatile uint32_t *ConfigTemp =NULL;
ConfigTemp	=	GPIO_Pin->GPIO_Pin < GPIO_PIN_8 ? &GPIOx->CRL: &GPIOx->CRH;
uint8_t Pin_Config =0;
	//Clear The bits that you'll write on//
		(*ConfigTemp) &= ~((0xF) << Get_CRLH_Position(GPIO_Pin->GPIO_Pin)) ;

		//if pin is output//
		if((GPIO_Pin->GPIO_Mode == GPIO_Mode_Output_OD) || (GPIO_Pin->GPIO_Mode == GPIO_Mode_Output_PP) || (GPIO_Pin->GPIO_Mode == GPIO_Mode_Output_AF_OD) ||(GPIO_Pin->GPIO_Mode == GPIO_Mode_Output_AF_PP))
		{						//cnf value								// Mode value						//Pin Position
				//(*ConfigTemp) |= (((GPIO_Pin->GPIO_Mode - 4)<<2) | (( GPIO_Pin->GPIO_Out_Speed<< 0) & 0x0F)) << Get_CRLH_Position(GPIO_Pin->GPIO_Pin)  ;
				//Set ODR
			Pin_Config  =  (  ( ( (GPIO_Pin->GPIO_Mode - 4) <<2 ) |  GPIO_Pin->GPIO_Out_Speed   ) & 0x0F );
			(*ConfigTemp) |= (  (  Pin_Config  ) << ( Get_CRLH_Position( GPIO_Pin->GPIO_Pin) ) ) ;

		}
		//Pin is input
		else {
			if ((GPIO_Pin->GPIO_Mode == GPIO_Mode_Input_FLO) || GPIO_Pin->GPIO_Mode ==GPIO_Mode_Analog )
									//CNF Value								//Pin Postion
	//		(*ConfigTemp) |= ((((GPIO_Pin->GPIO_Mode << 2)))  << ((Get_CRLH_Position (GPIO_Pin->GPIO_Pin)))) ;
				{
				Pin_Config  =  (  ( ( (GPIO_Pin->GPIO_Mode - 4) <<2 ) |  GPIO_Pin->GPIO_Out_Speed   ) & 0x0F );
				(*ConfigTemp) |= (  (  Pin_Config  ) << ( Get_CRLH_Position( GPIO_Pin->GPIO_Pin) ) ) ;

				}

			else if (GPIO_Pin-> GPIO_Mode ==GPIO_Mode_AF_Input )

			{	uint32_t ConfigODR= GPIOx->ODR;

						(*ConfigTemp) |= ((((GPIO_Mode_Input_FLO<< 2)))  << ((Get_CRLH_Position (GPIO_Pin->GPIO_Pin))));

						GPIO_Pin-> GPIO_Mode == GPIO_Mode_Input_PU ?  (ConfigODR |= GPIO_Pin->GPIO_Pin ) : (ConfigODR &= ~ (GPIO_Pin->GPIO_Pin)) ;
			}

		}

		/**
				No need it because the pointer will assign the values
		ConfigTemp == &(GPIOx->CRL)  ? (GPIOx->CRL= ConfigTemp) : (GPIOx->CRH = ConfigTemp);
		 	 	 */
}
/**================================================================
* @Fn						-GPIO_DeInit
* @brief 					- DeIntialize GPIO specific port and Specific Pin
* @param [in] 				-GPIOxn: where Port could Be (A,B,..etc)
* @retval 					-none
* Note						-none
*/
void GPIO_DeInit(GPIO_t * GPIOx){

	GPIOx->CRL = 0x44444444;
	GPIOx->CRH = 0x44444444;
	GPIOx->ODR = 0x00000000;
	GPIOx->BSRR = 0x00000000;
	GPIOx->BRR = 0x00000000;
	GPIOx->LCKR = 0x00000000;


/*
	if (GPIOx == GPIOA_Ptr)
	{
		RCC->APB2RSTR |= (1<<2);
			RCC->APB2RSTR &= ~(1<<2);

	}*/


}

/**================================================================
* @Fn						-GPIO_ReadPin
* @brief 					- Read Specific Pin
* @param [in] 				-GPIOx: where Port could Be (A,B,..etc)
** @param [in] 				-uint16_t GPIO_PIN : Specific Pin number, according GPIO @ref GPIO_Pin_State
* @retval 					- the input pin value (two based values) @ref GPIO_Pin_State
* Note						-none
*/

uint8_t GPIO_ReadPin(GPIO_t * GPIOx,uint16_t GPIO_PIN_Number){
	uint8_t bitStatus;
		// GPIOx->IDR & 1<<GPIO_PinNumber//
	if (((GPIOx->IDR) & GPIO_PIN_Number) != (uint32_t) GPIO_Pin_RSet)
	{
		  bitStatus= GPIO_Pin_Set;
	}
	else {
		bitStatus= GPIO_Pin_RSet;
	}
	return bitStatus;
}
/**================================================================
* @Fn						-GPIO_ReadPort
* @brief 					- Read Specific Pin
* @param [in] 				-GPIOx: Read Port could Be (A,B,..etc)
* @retval 					- the input port value (two based values) @ref GPIO_Port_State
* Note						-none
*/
uint16_t GPIO_ReadPort(GPIO_t * GPIOx){

uint16_t port_value;
port_value = (uint16_t)GPIOx->IDR;
return port_value;

}
/**================================================================
* @Fn						-GPIO_WritePin
* @brief 					- Write Specific Pin
* @param [in] 				-GPIOx: where Port could Be (A,B,..etc)
* @param [in] 				-uint16_t GPIO_PIN : Specific Pin number, according GPIO @ref
* @param [in] 				-uint8_t value : Specific Pin value, according GPIO @ref
*
* @retval 					- the input pin value (two based values) @ref GPIO_Pin_State
* Note						-none
*/


void GPIO_WritePin(GPIO_t * GPIOx,uint16_t GPIO_PIN_Number, uint8_t value){
	if (value != (uint32_t) GPIO_Pin_RSet)
	{
			GPIOx->BSRR =(uint32_t) GPIO_PIN_Number;
	}
	else{
		GPIOx->BRR =(uint32_t) GPIO_PIN_Number;
	}
}

/**================================================================
* @Fn						-GPIO_WritePort
* @brief 					- Write Specific Port
* @param [in] 				-GPIOx: where Port could Be (A,B,..etc)
* @param [in] 				-uint16_t value : Specific Pin value, according GPIO @ref
*
* @retval 					- the input pin value (two based values) @ref GPIO_Pin_State
* Note						-none
*/

void GPIO_WritePort(GPIO_t * GPIOx, uint16_t value){

	GPIOx->ODR = value;
}

/**================================================================
* @Fn						-GPIO_LockPin
* @brief 					- Allowing IO pin to be frozen
* @param [in] 				-GPIO_PortPtr: where Port could Be (A,B,..etc)
* @param [in] 				-uint16_t value : Specific Pin value, according GPIO @ref GPIO_Pins
*
* @retval 					- @GPIO_Ret_Lock
* Note						-none
*/

/*uint8_t GPIO_LockPin(GPIO_t * GPIOPort_Ptr, uint16_t GPIO_PIN){

}*/



//static functions implementation

static uint8_t Get_CRLH_Position(uint16_t GPIO_Pin_Number){
	switch (GPIO_Pin_Number)
	{
	case GPIO_PIN_0: return 0; break;
	case GPIO_PIN_1: return 4; break;
	case GPIO_PIN_2: return 8; break;
	case GPIO_PIN_3: return 12; break;
	case GPIO_PIN_4: return 16; break;
	case GPIO_PIN_5: return 20; break;
	case GPIO_PIN_6: return 24; break;
	case GPIO_PIN_7: return 28; break;

	case GPIO_PIN_8: return 0; break;
		case GPIO_PIN_9: return 4; break;
		case GPIO_PIN_10: return 8; break;
		case GPIO_PIN_11: return 12; break;
		case GPIO_PIN_12: return 16; break;
		case GPIO_PIN_13: return 20; break;
		case GPIO_PIN_14: return 24; break;
		case GPIO_PIN_15: return 28; break;
			default: return 0;break;
	}
	return 0;
}

void GPIO_Toggle (){
	GPIOA_Ptr->ODR ^= (GPIO_PIN_4);

}

