/*
 * GPIO_Test.c
 *
 *  Created on: 30 Jun 2023
 *      Author: Boufa
 */




#include "inc/stm_regs.h"
#include "inc/MRCC.h"
#include "inc/MGPIO.h"
#include "inc/HLCD.h"
#include "inc/MEXTI.h"

void clockinit(){


	RCC_GPIOA_CLK_EN();
	RCC_AFIO_CLK_EN();
}

void GPIOINIT(){
	GPIO_Pin_config_t Pincfg;
		Pincfg.GPIO_Pin = GPIO_PIN_1;
		Pincfg.GPIO_Mode =GPIO_Mode_Input_FLO;
		GPIO_Init(GPIOA_Ptr, &Pincfg);

			Pincfg.GPIO_Pin = GPIO_PIN_4;
			Pincfg.GPIO_Mode =GPIO_Mode_Output_PP;
			Pincfg.GPIO_Out_Speed = GPIO_Output_SPeed_10MHZ;
			GPIO_Init(GPIOA_Ptr, &Pincfg);

			Pincfg.GPIO_Pin = GPIO_PIN_10;
					Pincfg.GPIO_Mode =GPIO_Mode_Input_FLO;
					GPIO_Init(GPIOA_Ptr, &Pincfg);


					Pincfg.GPIO_Pin = GPIO_PIN_4;
					Pincfg.GPIO_Mode =GPIO_Mode_Output_PP;
					Pincfg.GPIO_Out_Speed = GPIO_Output_SPeed_10MHZ;
					GPIO_Init(GPIOA_Ptr, &Pincfg);


}

/*void main ()
{
	clockinit();
	//GPIOINIT();
	GPIO_Pin_config_t Pincfg;
			Pincfg.GPIO_Pin = GPIO_PIN_1;
			Pincfg.GPIO_Mode =GPIO_Mode_Input_FLO;
			GPIO_Init(GPIOA_Ptr, &Pincfg);

				Pincfg.GPIO_Pin = GPIO_PIN_4;
				Pincfg.GPIO_Mode =GPIO_Mode_Output_PP;
				Pincfg.GPIO_Out_Speed = GPIO_Output_SPeed_10MHZ;
				GPIO_Init(GPIOA_Ptr, &Pincfg);

				Pincfg.GPIO_Pin = GPIO_PIN_10;
						Pincfg.GPIO_Mode =GPIO_Mode_Input_FLO;
						GPIO_Init(GPIOA_Ptr, &Pincfg);


						Pincfg.GPIO_Pin = GPIO_PIN_4;
						Pincfg.GPIO_Mode =GPIO_Mode_Output_PP;
						Pincfg.GPIO_Out_Speed = GPIO_Output_SPeed_10MHZ;
						GPIO_Init(GPIOA_Ptr, &Pincfg);


while (1){
	if (GPIO_ReadPin(GPIOA_Ptr,GPIO_PIN_1) == 0) // press
	{
				GPIO_Toggle ();
			while(GPIO_ReadPin(GPIOA_Ptr,GPIO_PIN_1) == 0);
	}

}

}
*/

// ----------------------------------------------------------------------------
