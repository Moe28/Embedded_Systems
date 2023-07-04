/*
 * MEXTI.h
 *
 *  Created on: 29 Jun 2023
 *      Author: Boufa
 */

#ifndef INC_MEXTI_H_
#define INC_MEXTI_H_
/*************************************************
 * Includes
 * ***********************************************/
#include "MGPIO.h"

#include  "stm_regs.h"
/*************************************************
 * defines
 * ***********************************************/


/*************************************************
 * Configure Structs/ Enum
 * ***********************************************/

typedef struct{
 GPIO_t* GPIO_Port;
	uint16_t EXTI_Line; // External Input line Number
	uint16_t GPIO_PIN;
	uint8_t IVT_IRQ_Number; //  IVT Number Based on Vector Table
}EXTI_GPIO_Mapping_t;

typedef struct{
	uint8_t Trigger_Case; // Specifies Trigger cases Falling or Rising or Both @ref Trigger_Cases
	uint8_t IRQ_EN;  // Enable Or Disable the EXTI IRQ (That will enable the IRQ ON EX\I also on NVIC) @refIRQ_Enable
	EXTI_GPIO_Mapping_t EXTIPin; //Mapping the EXTI PIN requirments based on EXTI port, line, pin and IRQ Number from vector table @ref EXTI_Pinconfig_t
	void (*Ptr_IRQ_CallBack)(void);
}EXTI_Pinconfig_t;

/*************************
 * Macros Configuration
 * **********************/
//@ref Trigger_Cases

#define EXTI_Falling			1
#define EXTI_Rising				0
#define EXTI_Rising_Falling		2
//@refIRQ_Enable

#define EXTI_IRQ_Enable		1
#define EXTI_IRQ_Disable	0

//@ref EXTI_Line
#define EXTI_Line_0	    	    0
#define EXTI_Line_1	   			1
#define EXTI_Line_2	    	   	2
#define EXTI_Line_3	       		3
#define EXTI_Line_4	      	    4
#define EXTI_Line_5	       		5
#define EXTI_Line_6	       		6
#define EXTI_Line_7	       		7
#define EXTI_Line_8	       		8
#define EXTI_Line_9	       		9
#define EXTI_Line_10	       10
#define EXTI_Line_11	       11
#define EXTI_Line_12	       12
#define EXTI_Line_13	       13
#define EXTI_Line_14	       14
#define EXTI_Line_15       	   15



#define EXTI_0
//@ref EXTI_Pinconfig_t
extern  GPIO_t * const GPIOA_Ptr ;
extern  GPIO_t * const GPIOB_Ptr ;

// EXTIPA0 {EXTI_Line_0,GPIOA,GPIO_PIN0, EXTI_IRQ0}
#define EXTIPA0         (EXTI_GPIO_Mapping_t) {GPIOA_BASE,EXTI_Line_0,GPIO_PIN_0,EXTI0_IRQ}
#define EXTIPB0         (EXTI_GPIO_Mapping_t) {GPIOB_BASE,EXTI_Line_0,GPIO_PIN_0,EXTI0_IRQ}
#define EXTIPA1         (EXTI_GPIO_Mapping_t) {GPIOA_BASE,EXTI_Line_1,GPIO_PIN_1,EXTI1_IRQ}
#define EXTIPB1         (EXTI_GPIO_Mapping_t) {GPIOB_BASE,EXTI_Line_1,GPIO_PIN_1,EXTI1_IRQ}
#define EXTIPA2         (EXTI_GPIO_Mapping_t) {GPIOA_BASE,EXTI_Line_2,GPIO_PIN_2,EXTI2_IRQ}
#define EXTIPB2         (EXTI_GPIO_Mapping_t) {GPIOB_BASE,EXTI_Line_2,GPIO_PIN_2,EXTI2_IRQ}
#define EXTIPA3         (EXTI_GPIO_Mapping_t) {GPIOA_BASE,EXTI_Line_3,GPIO_PIN_3,EXTI3_IRQ}
#define EXTIPB3         (EXTI_GPIO_Mapping_t) {GPIOB_BASE,EXTI_Line_3,GPIO_PIN_3,EXTI3_IRQ}
#define EXTIPA4         (EXTI_GPIO_Mapping_t) {GPIOA_BASE,EXTI_Line_4,GPIO_PIN_4,EXTI4_IRQ}
#define EXTIPB4         (EXTI_GPIO_Mapping_t) {GPIOB_BASE,EXTI_Line_4,GPIO_PIN_4,EXTI4_IRQ}
#define EXTIPA5         (EXTI_GPIO_Mapping_t) {GPIOA_BASE,EXTI_Line_5,GPIO_PIN_5,EXTI5_IRQ}
#define EXTIPB5         (EXTI_GPIO_Mapping_t) {GPIOB_BASE,EXTI_Line_5,GPIO_PIN_5,EXTI5_IRQ}
#define EXTIPA6         (EXTI_GPIO_Mapping_t) {GPIOA_BASE,EXTI_Line_6,GPIO_PIN_6,EXTI6_IRQ}
#define EXTIPB6         (EXTI_GPIO_Mapping_t) {GPIOB_BASE,EXTI_Line_6,GPIO_PIN_6,EXTI6_IRQ}
#define EXTIPA7         (EXTI_GPIO_Mapping_t) {GPIOA_BASE,EXTI_Line_7,GPIO_PIN_7,EXTI7_IRQ}
#define EXTIPB7         (EXTI_GPIO_Mapping_t) {GPIOB_BASE,EXTI_Line_7,GPIO_PIN_7,EXTI7_IRQ}
#define EXTIPA8         (EXTI_GPIO_Mapping_t) {GPIOA_BASE,EXTI_Line_8,GPIO_PIN_8,EXTI8_IRQ}
#define EXTIPB8         (EXTI_GPIO_Mapping_t) {GPIOB_BASE,EXTI_Line_8,GPIO_PIN_8,EXTI8_IRQ}
#define EXTIPA9         (EXTI_GPIO_Mapping_t) {GPIOA_Ptr,EXTI_Line_9,GPIO_PIN_9,EXTI9_IRQ}
#define EXTIPB9         (EXTI_GPIO_Mapping_t) {GPIOB_BASE,EXTI_Line_9,GPIO_PIN_9,EXTI9_IRQ}
#define EXTIPA10        (EXTI_GPIO_Mapping_t) {GPIOA_BASE,EXTI_Line_10,GPIO_PIN_10,EXTI10_IRQ}
#define EXTIPB10        (EXTI_GPIO_Mapping_t) {GPIOB_BASE,EXTI_Line_10,GPIO_PIN_10,EXTI10_IRQ}
#define EXTIPA11        (EXTI_GPIO_Mapping_t) {GPIOA_BASE,EXTI_Line_11,GPIO_PIN_11,EXTI11_IRQ}
#define EXTIPB11        (EXTI_GPIO_Mapping_t) {GPIOB_BASE,EXTI_Line_11,GPIO_PIN_11,EXTI11_IRQ}
#define EXTIPA12        (EXTI_GPIO_Mapping_t) {GPIOA_BASE,EXTI_Line_12,GPIO_PIN_12,EXTI12_IRQ}
#define EXTIPB12        (EXTI_GPIO_Mapping_t) {GPIOB_BASE,EXTI_Line_12,GPIO_PIN_12,EXTI12_IRQ}
#define EXTIPA13        (EXTI_GPIO_Mapping_t) {GPIOA_BASE,EXTI_Line_13,GPIO_PIN_13,EXTI13_IRQ}
#define EXTIPB13        (EXTI_GPIO_Mapping_t) {GPIOB_BASE,EXTI_Line_13,GPIO_PIN_13,EXTI13_IRQ}
#define EXTIPA14        (EXTI_GPIO_Mapping_t) {GPIOA_BASE,EXTI_Line_14,GPIO_PIN_14,EXTI14_IRQ}
#define EXTIPB14        (EXTI_GPIO_Mapping_t) {GPIOB_BASE,EXTI_Line_14,GPIO_PIN_14,EXTI14_IRQ}
#define EXTIPA15        (EXTI_GPIO_Mapping_t) {GPIOA_BASE,EXTI_Line_15,GPIO_PIN_15,EXTI15_IRQ}
#define EXTIPB15        (EXTI_GPIO_Mapping_t) {GPIOB_BASE,EXTI_Line_15,GPIO_PIN_15,EXTI15_IRQ}
/*********
 #define EXTIPA15		(EXTI_GPIO_Mapping_t) {GPIOA_BASE,EXTI_Line_2,GPIO_PIN_2,EXTI_2}
#define EXTIPB15		(EXTI_GPIO_Mapping_t) {GPIOB_BASE,EXTI_Line_2,GPIO_PIN_2,EXTI_2}
 *
 */
/*************************************************
APIs Prototypes
 * ***********************************************/

void Ext_GPIO_Init(EXTI_Pinconfig_t* EXTI_Pin);
void Ext_GPIO_DeInit(void);
void Ext_GPIO_Update(EXTI_Pinconfig_t* EXTI_Pin);




#endif /* INC_MEXTI_H_ */
