#include "uart.h"

unsigned char string_buffer[100]= "Learn-in-depth:Shehata";

void main (void)
{
	
	Uart_Send_string (string_buffer);
		
}