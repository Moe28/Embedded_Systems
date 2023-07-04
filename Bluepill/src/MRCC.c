/*
 * MRCC.c
 *
 *  Created on: 29 Jun 2023
 *      Author: Boufa
 */


#include "inc/MRCC.h"

#define RCC_Ptr_BASE    	0x40021000UL //unsigned long
typedef struct{
	volatile uint32_t CR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t APB2RSTR;
	volatile uint32_t APB1RSTR;
	volatile uint32_t AHBENR;
	volatile uint32_t APB2ENR;
	volatile uint32_t APB1ENR;
	volatile uint32_t BDCR;
	volatile uint32_t CSR;
	volatile uint32_t AHBSTR;
	volatile uint32_t CFGR2;

}RCC_Ptr_t;

volatile   RCC_Ptr_t * const RCC_Ptr	 = 		(volatile RCC_Ptr_t * const )RCC_Ptr_BASE;






//PPRE1[2:0]: APB Low-speed prescaler (APB1)
//0xx: HCLK not divided
//100: HCLK divided by 2
//101: HCLK divided by 4
//110: HCLK divided by 8
//111: HCLK divided by 16
const uint8_t APBPrescTable[8U] =  {0, 0, 0, 0, 1, 2, 3, 4}; //Shift 1 right == mutliply by 2


//Bits 7:4 HPRE[3:0]: AHB prescaler
//Set and cleared by software to control AHB clock division factor.
//0xxx: SYSCLK not divided
//1000: SYSCLK divided by 2
//1001: SYSCLK divided by 4
//1010: SYSCLK divided by 8
//1011: SYSCLK divided by 16
//1100: SYSCLK divided by 64
//1101: SYSCLK divided by 128
//1110: SYSCLK divided by 256
//1111: SYSCLK divided by 512
const uint8_t AHBBPrescTable[16U] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 6, 7, 8, 9};


/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */



/*
 * =======================================================================================
 * 							Generic Macros
 * =======================================================================================
 */
//#define RCC_GPIOA_CLK_EN()		(RCC_Ptr->APB2ENR |= 1<<2)
//#define RCC_GPIOB_CLK_EN()		(RCC_Ptr->APB2ENR |= 1<<3)
//#define RCC_GPIOC_CLK_EN()		(RCC_Ptr->APB2ENR |= 1<<2)
//#define RCC_AFIO_CLK_EN()			(RCC_Ptr->APB2ENR |= 1<<0)

/*
 * =======================================================================================
 * 							Generic Functions
 * =======================================================================================
 */


void RCC_AFIO_CLK_EN(){
	(RCC_Ptr->APB2ENR |= 1<<0);
}

void RCC_GPIOA_CLK_EN(){
	(RCC_Ptr->APB2ENR |= 1<<2);
}

uint32_t MCAL_RCC_Ptr_GetSYS_CLCKFreq(void)
{

//	Bits 3:2 SWS[1:0]: System clock switch status
//	Set and cleared by hardware to indicate which clock source is used as system clock.
//	00: HSI oscillator used as system clock
//	01: HSE oscillator used as system clock
//	10: PLL used as system clock
//	11: Not applicable
	switch  ( (RCC_Ptr->CFGR  >> 2  ) & 0b11 )
	{
	case 0:

		return HSI_RC_Clk ;
		break ;

	case 1:

		//todo need to calculate  it //HSE User Should Specify it
		return HSE_Clock ;
		break ;

	case 2:

		//todo need to calculate  it PLLCLK and PLLMUL & PLL Source MUX
		return 16000000 ;
		break ;

	}

}


uint32_t MCAL_RCC_Ptr_GetHCLKFreq(void)
{
	/* Get HCLK source and Compute PCLK1 frequency ---------------------------*/
	return (MCAL_RCC_Ptr_GetSYS_CLCKFreq() >> AHBBPrescTable[ ( (RCC_Ptr->CFGR >> 4 ) & 0xF) ]  ); //the first shift is multiplication}
}

//APB Low speed clock (PCLK1).
//Bits 10:8 PPRE1[2:0]: APB Low-speed prescaler (APB1)
uint32_t MCAL_RCC_Ptr_GetPCLK1Freq(void)
{
	/* Get HCLK source and Compute PCLK1 frequency ---------------------------*/
	return (MCAL_RCC_Ptr_GetHCLKFreq() >> APBPrescTable[ ( (RCC_Ptr->CFGR >> 8 ) & 0b111) ]  ); //the first shift is multiplication
}

uint32_t MCAL_RCC_Ptr_GetPCLK2Freq(void)
{
	/* Get HCLK source and Compute PCLK2 frequency ---------------------------*/
	return (MCAL_RCC_Ptr_GetHCLKFreq() >> APBPrescTable[ ( (RCC_Ptr->CFGR >> 11 ) & 0b111) ]  ); //the first shift is multiplication
}


