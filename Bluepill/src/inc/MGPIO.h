/*
 * MGPIO.h
 *
 *  Created on: 29 Jun 2023
 *      Author: Boufa
 */

#ifndef INC_MGPIO_H_
#define INC_MGPIO_H_


/*************************************************
 * Includes
 * ***********************************************/
#include  "stm_regs.h"

/*************************************************
 * defines
 * ***********************************************/
typedef struct GPIO_reg GPIO_t;


/*************************************************
 * Configure Structs/ Enum
 * ***********************************************/


typedef struct
{
//	uint32_t 	GPIO_Port; /*A,B,C*/
  uint16_t GPIO_Pin;       /* Specifies the GPIO pins to be configured.
                           @ref GPIO_pins_define */

  uint32_t GPIO_Mode;      /* Specifies the operating mode for the selected pins.
                            @ref GPIO_mode_define */


  uint32_t GPIO_Out_Speed;     /* Specifies the speed for the selected pins.
                           @ref GPIO_speed_define */

}GPIO_Pin_config_t;



//@ref GPIO_Pin_State

#define GPIO_Pin_Set 	0
#define GPIO_Pin_RSet 	1

//@ref GPIO_Port_State
#define GPIO_Port_Set 		1
#define GPIO_Port_SRSet 	0


//@ref  GPIO_Ret_Lock

#define  GPIO_Ret_Lock_En 	1
#define  GPIO_Ret_Lock_Err 	0

/*************************************************
 * Macro Configuration References
 * ***********************************************/
//@ref GPIO_PinsDefine
#define GPIO_PIN_0 		((uint16_t)0x0001) //PIN0
#define GPIO_PIN_1 		((uint16_t)0x0002) //PIN1
#define GPIO_PIN_2 		((uint16_t)0x0004) //PIN2
#define GPIO_PIN_3 		((uint16_t)0x0008) //PIN3
#define GPIO_PIN_4 		((uint16_t)0x0010) //PIN4
#define GPIO_PIN_5 		((uint16_t)0x0020) //PIN5
#define GPIO_PIN_6 		((uint16_t)0x0040) //PIN6
#define GPIO_PIN_7 		((uint16_t)0x0080) //PIN7
#define GPIO_PIN_8 		((uint16_t)0x0100) //PIN8
#define GPIO_PIN_9 		((uint16_t)0x0200) //PIN9
#define GPIO_PIN_10 	((uint16_t)0x0400) //PIN10
#define GPIO_PIN_11 	((uint16_t)0x0800) //PIN11
#define GPIO_PIN_12 	((uint16_t)0x1000) //PIN12
#define GPIO_PIN_13	 	((uint16_t)0x2000) //PIN13
#define GPIO_PIN_14		((uint16_t)0x4000) //PIN14
#define GPIO_PIN_15 	((uint16_t)0x8000) //PIN15
#define GPIO_PIN_ALL 	((uint16_t)0xFFFF) //PINAL

#define GPIO_PIN_MASK 0x0000FFFFu /*Pin Mask*/

//@ref GPIO_ModesDefine
/*These bits are written by software to configure the I/O direction mode.
0: Analog mode
1: Floating input (reset state)
2: Input with pull-up / pull-down
3: Pull-down
4: General purpose output push-pull
5: General purpose output Open-drain
6: Alternate function output Push-pull
7: Alternate function output Open-drain
8:Alternative function Input
 * */
//GPIO port mode register
#define GPIO_Mode_Analog				 	0x00000000
#define GPIO_Mode_Input_FLO			 		0x00000001
#define GPIO_Mode_Input_PU		 			0x00000002
#define GPIO_Mode_Input_PD					0x00000003
#define GPIO_Mode_Output_PP					0x00000004
#define GPIO_Mode_Output_OD					0x00000005
#define GPIO_Mode_Output_AF_PP				0x00000006
#define GPIO_Mode_Output_AF_OD				0x00000007
#define GPIO_Mode_AF_Input					0x00000008






/*
 GPIO_Speed
 OSPEEDRy[1:0]: Port x configuration bits (y = 0..15)
These bits are written by software to configure the I/O output speed.
01: Output mode, max speed 10 MHz.
10: Output mode, max speed 2 MHz.
11: Output mode, max speed 50 MHz.
 *
 * **/

#define GPIO_Output_SPeed_10MHZ			0x00000001
#define GPIO_Output_SPeed_2MHZ			0x00000002
#define GPIO_Output_SPeed_50MHZ			0x00000003



//extern GPIO_t;

void GPIO_Init(GPIO_t* GPIOx, GPIO_Pin_config_t* GPIO_Pin);
void GPIO_DeInit(GPIO_t * GPIOx);
uint8_t GPIO_ReadPin(GPIO_t * GPIOx,uint16_t GPIO_PIN_Number);
uint16_t GPIO_ReadPort(GPIO_t * GPIOx);
void GPIO_WritePin(GPIO_t * GPIOx,uint16_t GPIO_PIN_Number, uint8_t value);
void GPIO_WritePort(GPIO_t * GPIOx, uint16_t value);
void GPIO_Toggle();
//uint8_t GPIO_LockPin(GPIO_t * GPIOPort_Ptr, uint16_t GPIO_PIN);



#endif /* INC_MGPIO_H_ */
