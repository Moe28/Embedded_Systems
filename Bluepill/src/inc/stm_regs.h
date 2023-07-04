/*
 * stm_regs.h
 *
 *  Created on: 29 Jun 2023
 *      Author: Boufa
 */

#ifndef INC_STM_REGS_H_
#define INC_STM_REGS_H_
/*********************************************************
 *
 * Includes
 *
 *********************************************************/
#include "stdlib.h"
#include "stdint.h"

/*********************************************************
 *
 * Base Address for memory
 *
 *********************************************************/
#define Flash_Memory_Base 				0x08000000UL
#define System_Memory_Base				0x1FFFF000UL
#define SRAM_Memory_Base				0x20000000UL

#define Peripherals_Base				0x40000000UL
#define Cortex_M3_Internal_Peripherals	0xE0000000UL


/*********************************************************
 *
 * Base Address for AHB1_Peripherals
 *
 *********************************************************/

//#define RCC_BASE    	0x40021000UL //unsigned long

/*********************************************************
 *
 * Base Address for APB2_Peripherals
 *
 *********************************************************/

#define AFIO_BASE 			0x40010000UL
//#define EXTI_BASE			0x40010400UL
//#define GPIOA_BASE 			0x40010800UL
//#define GPIOB_BASE 			0x40010C00UL
//#define GPIOC_BASE 			0x40011000UL

#define TIM1_Base			0x40012C00UL
#define USART1 				0x40013800UL
/*********************************************************
 *
 * Cortex Main Peripherals
 *
 *PP_Bus
 *********************************************************/
#define NVIC_BASE			0xE000E100UL
#define SCB_BASE			0xE000ED00UL
//=====================================================================
/*********************************************************
 *
 * Peripherals_Register
 *
 *********************************************************/

/*********************************************************
 *
 * Peripherals_Register_GPIO
 *********************************************************/
//typedef struct {
//	uint32_t CRL;
//	uint32_t CRH;
//	uint32_t IDR;
//	uint32_t ODR;
//	uint32_t BSRR;
//	uint32_t BRR;
//	uint32_t LCKR;
//
//}GPIO_t;

/*********************************************************
 *
 * Peripherals_Register_RCC
 *********************************************************/
//typedef struct{
//	volatile uint32_t CR;
//	volatile uint32_t CFGR;
//	volatile uint32_t CIR;
//	volatile uint32_t APB2RSTR;
//	volatile uint32_t APB1RSTR;
//	volatile uint32_t AHBENR;
//	volatile uint32_t APB2ENR;
//	volatile uint32_t APB1ENR;
//	volatile uint32_t BDCR;
//	volatile uint32_t CSR;
//	volatile uint32_t AHBSTR;
//	volatile uint32_t CFGR2;
//
//}RCC_t;

/*********************************************************
 *
 * Peripherals_Register_AFIO
 *********************************************************/
typedef struct{
volatile uint32_t EVCR;
volatile uint32_t MAPR;
volatile uint32_t EVCEXTICR[4];
uint32_t reserved;
volatile uint32_t MAPR2;

}AFIO_t;
/*********************************************************
 *
 * Peripherals_Register_EXT1
 *********************************************************/
//typedef struct{
//
//	volatile uint32_t IMR;
//	volatile uint32_t EMR;
//	volatile uint32_t RTSR;
//	volatile uint32_t FTSR;
//	volatile uint32_t SWIER;
//	volatile uint32_t PR;
//
//}EXTI_t;


//=====================================================================
/*********************************************************
 *
 *Cortex Peripherals_Register
 *
 *********************************************************/

/*********************************************************
 *
 * Peripherals_Register_NVIC
 *********************************************************/
/*
typedef struct
{
	 uint32_t ISER[3]; 			// SET ENABLE Interrupt
	 uint32_t RESRVED_1[29];
	 uint32_t ICER[3]; 			// CLEAR DISABLE Interrupt
	 uint32_t RESRVED_2[29];
	 uint32_t ISPR[3]; 			// SET PENDING Interrupt
	 uint32_t RESRVED_3[29];
	 uint32_t ICPR[3]; 			// CLEAR PENDING Interrupt
	 uint32_t RESRVED_4[29];
	 uint32_t IABR[3];			// READ ACTIVE Interrupt
	 uint32_t RESRVED_5[61];
	 uint8_t  IPR[84];			// SET Priority Interrupt
	 uint32_t RESRVED_6[695];
	 uint32_t STIR;				// SET/CLEAR Software Interrupt (8-bits interrupt ID from 0-239)
}NVIC_t;
*/

#define NVIC_ISER0 		*(volatile uint32_t *)(NVIC_BASE+0x00)
#define NVIC_ISER1		*(volatile uint32_t *)(NVIC_BASE+0x4)
#define NVIC_ISER2		*(volatile uint32_t *)(NVIC_BASE+0x8)

#define NVIC_ICER0 		*(volatile uint32_t *)(NVIC_BASE+0x80)
#define NVIC_ICER1 		*(volatile uint32_t *)(NVIC_BASE+0x84)
#define NVIC_ICER2 		*(volatile uint32_t *)(NVIC_BASE+0x88)

#define SCB_AIRCR_REG         *(volatile uint32_t *)(SCB_BASE+ 0x0C)
/*********************************************************
 *
 * Peripherals_Instants (POINTERS)
 *
 *********************************************************/

//static volatile   RCC_t * const RCC_Ptr 	 = 		(volatile RCC_t * const )RCC_BASE;
//static	volatile GPIO_t * const GPIOA_Ptr 	 = 		(volatile GPIO_t * const )GPIOA_BASE;
//static	volatile GPIO_t * const GPIOB_Ptr 	 = 		(volatile GPIO_t * const )GPIOB_BASE;


static volatile AFIO_t * const AFIO_Ptr 	 = 		(volatile AFIO_t * const )AFIO_BASE;

//static  volatile EXTI_t * const EXTI_Ptr     = 		(volatile EXTI_t * const) EXTI_BASE;


//static volatile NVIC_t * const NVIC_Ptr	= 		(volatile NVIC_t * const)NVIC_BASE;

//volatile uint32_t * const  SCB_AIRCR_REG_Ptr  = 		(volatile  uint32_t* const)SCB_AIRCR_REG;
/*********************************************************
 *
 * Clock Enable Macros
 *
 *********************************************************/
//
//#define RCC_GPIOA_CLK_EN()		(RCC_Ptr->APB2ENR |= 1<<2)
//#define RCC_GPIOB_CLK_EN()		(RCC_Ptr->APB2ENR |= 1<<3)
//#define RCC_GPIOC_CLK_EN()		(RCC_Ptr->APB2ENR |= 1<<2)
//#define RCC_AFIO_CLK_EN()			(RCC_Ptr->APB2ENR |= 1<<0)

/*********************************************************
 *
				IVT
 *********************************************************/
#define EXTI0_IRQ		6
#define EXTI1_IRQ		7
#define EXTI2_IRQ		8
#define EXTI3_IRQ		9
#define EXTI4_IRQ		10
#define EXTI5_IRQ		23
#define EXTI6_IRQ		23
#define EXTI7_IRQ		23
#define EXTI8_IRQ		23
#define EXTI9_IRQ		23
#define EXTI10_IRQ		40

/*********************************************************
 * 		NVIC IRQ Enable and Disable Macros
 *********************************************************/

#define NVIC_IRQ6_EXT0_Enable		(NVIC_ISER0 |= 1<<6)
#define NVIC_IRQ7_EXT1_Enable		(NVIC_ISER0 |= 1<<7)
#define NVIC_IRQ8_EXT2_Enable		(NVIC_ISER0 |= 1<<8)
#define NVIC_IRQ9_EXT3_Enable		(NVIC_ISER0 |= 1<<9)
#define NVIC_IRQ10_EXT4_Enable		(NVIC_ISER0 |= 1<<10)
#define NVIC_IRQ23_EXT5_9_Enable		(NVIC_ISER0 |= 1<<23)
#define NVIC_IRQ40_EXT10_15_Enable		(NVIC_ISER1 |= 1<<8) //40-32=8



#define NVIC_IRQ6_EXT0_Disable		(NVIC_ICER0 |= 1<<6)
#define NVIC_IRQ7_EXT1_Disable		(NVIC_ICER0 |= 1<<7)
#define NVIC_IRQ8_EXT2_Disable		(NVIC_ICER0 |= 1<<8)
#define NVIC_IRQ9_EXT3_Disable		(NVIC_ICER0 |= 1<<9)
#define NVIC_IRQ10_EXT4_Disable		(NVIC_ICER0 |= 1<<10)
#define NVIC_IRQ23_EXT5_9_Disable	(NVIC_ICER0 |= 1<<23)
#define NVIC_IRQ40_EXT10_15_Disable	(NVIC_ICER1 |= 1<<8) //40-32=8





#endif /* INC_STM_REGS_H_ */
