#include <stdint.h>


typedef  unsigned int unint32_t;
//#define STACK_Start_SP 0x20001000

void Reset_Handler();
extern void main();

void Default_Handler()
{
	Reset_Handler();
}

void NMI_handler() __attribute__ ((weak, alias("Default_Handler")));;
void H_FAULT_handler(void) __attribute__ ((weak, alias("Default_Handler")));;
void MM_Fault() __attribute__ ((weak, alias("Default_Handler")));;

//booking 1024 bytes located by .bss unintialized arr of int 256 element
static unsigned long  Stack_top [256];

	

void (*const g_p_fn_Vectors[])() __attribute__((section(".vectors"))) =
	{
			(void (*)()) ((unsigned long)Stack_top + sizeof(Stack_top)), // Stack pointer
			 &Reset_Handler,
			 &NMI_handler,
			 &H_FAULT_handler,
		
		};
	//************************************************
/*unint32_t Vector_Arr[] __attribute__((section(".vectors")))  =
{
	(unint32_t) &(Stack_top[0]+sizeof(Stack_top)), 
	(unint32_t) &Reset_Handler,
	(unint32_t) &NMI_handler,
	(unint32_t)	&H_FAULT_handler,
	
	};*/
	extern unsigned int _E_text;
	extern unsigned int _S_Data;
	extern unsigned int _E_Data;
	extern unsigned int _S_bss;
	extern unsigned int _E_bss;

void Reset_Handler()
{
	// copy data section from flash to Ram//
	unsigned int Data_size = (unsigned char *)&_E_Data - (unsigned char *)&_S_Data ;
	unsigned char* P_src = (unsigned char *)&_E_text;
	unsigned char* P_dst = (unsigned char *)&_S_Data;
	for (int i =0 ; i<Data_size ; i++)
	{
		 *((unsigned char*)P_dst++) = *((unsigned char*)(long )*P_src++) ;
	}
	
	// init .bss section in SRAM =0
		unsigned int bss_size = (unsigned char *)&_E_bss - (unsigned char *)&_S_bss ;

	for (int i =0 ; i<bss_size ; i++)
	{
		 *((unsigned char*)P_dst++) = (unsigned char)0 ;
	}
	
	//jump main()'
	
	main();
	
}
