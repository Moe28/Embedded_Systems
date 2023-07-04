

/*
#define SYSTCL_RCGC2_R    	 (*((volatile unsigned long*)0x400FE108))
#define GPIO_PORTF_DATA_R    (*((volatile unsigned long*)0x400253FC))
#define GPIO_PORTF_DIR_R    	 (*((volatile unsigned long*)0x40025400))
#define GPIO_PORTF_DEN_R       (*((volatile unsigned long*)0x4002551C))


int main ()
{
	volatile unsigned long  delay_count;
	
	SYSTCL_RCGC2_R= 0x20;
	//delay to make sure GPIOF is up running
	for( delay_count=0; delay_count<200; delay_count++);
	
	GPIO_PORTF_DIR_R |= 1<<3; //DIR is output for pin3 port F
	GPIO_PORTF_DEN_R |= 1<<3;
	while(1)
	{
		GPIO_PORTF_DATA_R |=1<<3;
			farmor( delay_count=0; delay_count<200000; delay_count++);
			GPIO_PORTF_DATA_R &= ~(1<<3);
			for( delay_count=0; delay_count<200000; delay_count++);

	}
	
	return 0;
}*/
#include "stdint.h"
#include "stdio.h"





#define GPIOA_BASE 		0x40020000UL
#define GPIO_Mode_Input 		 0x00000000
#define GPIO_Mode_GP_Output		 0x00000001
#define GPIO_Mode_Alternate		 0x00000002
#define GPIO_Mode_Analog		 0x00000003


typedef struct {
	uint32_t MODER;
	uint32_t OTYPER;
	uint32_t OSPEEDR;
	uint32_t PUPDR;
	uint32_t IDR;
	uint32_t ODR;
	uint32_t BSRR;
	uint32_t LCKR;
	uint32_t AFRL;
	uint32_t AFRH;

}GPIO_t;


typedef struct
{
  uint32_t GPIO_Pin;       /* Specifies the GPIO pins to be configured.
                           @ref GPIO_pins_define */

  uint32_t GPIO_Mode;      /* Specifies the operating mode for the selected pins.
                            @ref GPIO_mode_define */

  uint32_t GPIO_Pull;      /* Specifies the Pull-up or Pull-Down activation for the selected pins.
                            @ref GPIO_pull_define */

  uint32_t GPIO_Speed;     /* Specifies the speed for the selected pins.
                           @ref GPIO_speed_define */

  uint32_t GPIO_Alternate;  /* Peripheral to be connected to the selected pins.
                             @ref GPIO_Alternate_function_selection */
  uint32_t GPIO_Output_Type;
}GPIO_Pin_config_t;


volatile GPIO_t * const GPIOA_Ptr 	 = 		(volatile GPIO_t * const )GPIOA_BASE;




void GPIO_Init(GPIO_t* GPIOPort_Ptr , GPIO_Pin_config_t* GPIO_Pin){
	//Clear mode [1,0]//


	uint32_t temp = GPIOPort_Ptr->MODER ;
	temp &= ~(0x3 << (GPIO_Pin->GPIO_Pin)*2);

		temp |= ((GPIO_Pin->GPIO_Pull)<<(GPIO_Pin->GPIO_Pin)*2);
		GPIOPort_Ptr->MODER =temp;


	//if pin is input &	//if pin is Alternate Func

		if (GPIO_Pin->GPIO_Mode == GPIO_Mode_Input || GPIO_Pin->GPIO_Mode ==GPIO_Mode_Analog )
		{
				temp= GPIOPort_Ptr->PUPDR;
				temp &= ~(0x3 << (GPIO_Pin->GPIO_Pin)*2);
				temp |= ((GPIO_Pin->GPIO_Pull)<<(GPIO_Pin->GPIO_Pin)*2);

		}



		//if pin is out pit 		//if pint is alet


		if (GPIO_Pin -> GPIO_Mode == GPIO_Mode_GP_Output  || GPIO_Pin -> GPIO_Mode ==GPIO_Mode_Alternate)
		{
			/*configure Otyper & configure PUPDR */
			temp =GPIOPort_Ptr->OSPEEDR;
			temp &= ~(0x3 << (GPIO_Pin->GPIO_Pin)*2);
			temp |= ((GPIO_Pin->GPIO_Speed)<<(GPIO_Pin->GPIO_Pin)*2);
			GPIOPort_Ptr->OSPEEDR= temp;

				temp = GPIOPort_Ptr -> OTYPER  ;
				temp &= ~(0x1 << (GPIO_Pin->GPIO_Pin)*2);
							temp |= ((GPIO_Pin->GPIO_Output_Type)<<(GPIO_Pin->GPIO_Pin)*2);
							GPIOPort_Ptr -> OTYPER  = temp ;

		}


// for (uint32_t i=0; i<sizeof(GPIO_Pin_config_t);i++)
	// {
		// printf("GPIO_Pin_Config %d",GPIO_Pin);
		// GPIO_Pin++;
	// }



}

int main ()
{
	
	
	GPIO_Pin_config_t*  gpio_Pin;
	gpio_Pin->GPIO_Pin= 0x0002;
	gpio_Pin->GPIO_Mode=GPIO_Mode_GP_Output;
	gpio_Pin->GPIO_Pull = 01;
	GPIO_Init(GPIOA_Ptr,gpio_Pin );
	// printf("The size of struct %d",sizeof(GPIO_Pin_config_t));
	
	return 0;
}