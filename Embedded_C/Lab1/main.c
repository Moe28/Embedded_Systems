#include <stdint.h>
/*Register addresses*/

typedef volatile unsigned int vuint32_t;

#define RCC_BASE    	0X40021000
#define GPIOA_BASE 		0X40010800
#define RCC_APP2ENR 	*(volatile unint32_t *)(RCC_BASE + 0x18)
#define GPIOA_CRH		*(volatile unint32_t *)(GPIOA_BASE + 0x04)	
#define GPIOA_ODR 		*(volatile unint32_t *)(GPIOA_BASE + 0x0C)

//Bit fields

#define RCC_IOPAEN (1<<2)
#define GPIOA13 	(1UL<<13)


typedef union
{
	vuint32_t 	all_fields;
	struct
	{
			vuint32_t		reserved:13 ;
			vuint32_t		P_13:1;
			
	}Pin;
}R_ODR_t; 


volatile	 R_ODR_t* R_ODR = (volatile R_ODR_t*)(GPIOA_BASE + 0x0C);
unsigned char g_variables[3]= {1,2,3};
unsigned char const const_variables[3]= {1,2,3};
  
 int main ()
 {
	 RCC_APP2ENR |= RCC_IOPAEN;
	 
	 GPIOA_CRH &= 0xFF0FFFFF;
	 GPIOA_CRH |= 0x00200000;
	 
	 R-ODR->Pin.P_13=1;
	 for (int i=0;i<5000; i++);
	 	 R-ODR->Pin.P_13=0;

	 	 for (int i=0;i<5000; i++);

 }