/*
 * MRCC.h
 *
 *  Created on: 29 Jun 2023
 *      Author: Boufa
 */

#ifndef INC_MRCC_H_
#define INC_MRCC_H_

#include  "stm_regs.h"



#define  HSE_Clock			(uint32_t)16000000
#define  HSI_RC_Clk			(uint32_t)8000000

void RCC_GPIOA_CLK_EN();
uint32_t MCAL_RCC_GetSYS_CLCKFreq(void);
uint32_t MCAL_RCC_GetHCLKFreq(void);
uint32_t MCAL_RCC_GetPCLK1Freq(void);
uint32_t MCAL_RCC_GetPCLK2Freq(void);





#endif /* INC_MRCC_H_ */
