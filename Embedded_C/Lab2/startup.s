/*Startup_CortexM3.s
Boufa*/



/*SRAM 0x20000000*/

.section .vectors  

.word 0x20001000 					/*Stack Top address*/
.word reset							/*    */
.word Vector_handler				/*_NMI_handler*/
.word Vector_handler				/*_HARD_FAULT_handler*/
.word Vector_handler				/*MM Fault/
.word Vector_handler				/*Bus Fault*/
.word Vector_handler				/*Usage Fault*/
.word Vector_handler				/*Reserved*/
.word Vector_handler				/*Reserved*/
.word Vector_handler				/*Reserved*/
.word Vector_handler				/*Reserved*/
.word Vector_handler				/*SV call*/
.word Vector_handler				/*Debug Reserved*/
.word Vector_handler				/*Reserved*/
.word Vector_handler				/*PendSV*/
.word Vector_handler				/*SysTick*/
.word Vector_handler				/*IRQ0*/
.word Vector_handler				/*IRQ1*/
.word Vector_handler				/*IRQ2*/
.word Vector_handler				/*......*/






.section .text

_reset:
	bl main
	b .
	
.thumb_func

Vector_handler:
	b _reset