/*
 * HLCD.c
 *
 *  Created on: 29 Jun 2023
 *      Author: Boufa
 */




#include "inc/HLCD.h"
GPIO_Pin_config_t PinCfg;

/******************
 * GENERIC Functions
 * ****************/
extern  GPIO_t * const  GPIOA_Ptr;

void delay_ms (uint32_t time)
{
	uint32_t i, j;
	for(i=0; i<time; i++)
		for (j=0; j<time; j++)
			;
}

void LCD_GPIO_Init ()
{

	PinCfg.GPIO_Pin= RS_SWITCH;
	PinCfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Output_SPeed_10MHZ;
	GPIO_Init(GPIOA_Ptr,&PinCfg );
	//GPIO_Init(GPIOA_Ptr, &PinCfg);
	PinCfg.GPIO_Pin= RW_SWTICH;
	PinCfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Output_SPeed_10MHZ;
	GPIO_Init(GPIOA_Ptr,&PinCfg );

	PinCfg.GPIO_Pin= EN_SWITCH;
	PinCfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Output_SPeed_10MHZ;
	GPIO_Init(GPIOA_Ptr,&PinCfg );

	//================================
	//Set the next 8 pins As Inputs
	PinCfg.GPIO_Pin= GPIO_PIN_0;
	PinCfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Output_SPeed_10MHZ;
	GPIO_Init(GPIOA_Ptr,&PinCfg );

	PinCfg.GPIO_Pin= GPIO_PIN_1;
	PinCfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Output_SPeed_10MHZ;
	GPIO_Init(GPIOA_Ptr,&PinCfg );

	PinCfg.GPIO_Pin= GPIO_PIN_2;
	PinCfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Output_SPeed_10MHZ;
	GPIO_Init(GPIOA_Ptr,&PinCfg );

	PinCfg.GPIO_Pin= GPIO_PIN_3;
	PinCfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Output_SPeed_10MHZ;
	GPIO_Init(GPIOA_Ptr,&PinCfg );

	PinCfg.GPIO_Pin= GPIO_PIN_4;
	PinCfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Output_SPeed_10MHZ;
	GPIO_Init(GPIOA_Ptr,&PinCfg );

	PinCfg.GPIO_Pin= GPIO_PIN_5;
	PinCfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Output_SPeed_10MHZ;
	GPIO_Init(GPIOA_Ptr,&PinCfg );

	PinCfg.GPIO_Pin= GPIO_PIN_6;
	PinCfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Output_SPeed_10MHZ;
	GPIO_Init(GPIOA_Ptr,&PinCfg );

	PinCfg.GPIO_Pin= GPIO_PIN_7;
	PinCfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Output_SPeed_10MHZ;
	GPIO_Init(GPIOA_Ptr,&PinCfg );

	PinCfg.GPIO_Pin= GPIO_PIN_8;
	PinCfg.GPIO_Mode = GPIO_Mode_Output_PP;
	PinCfg.GPIO_Out_Speed = GPIO_Output_SPeed_10MHZ;
	GPIO_Init(GPIOA_Ptr,&PinCfg );

	//	DataDir_GPIOA_Ptr |= (1 << EN_SWITCH | 1 << RS_SWITCH | 1 << RW_SWITCH);
	GPIO_WritePin(GPIOA_Ptr, EN_SWITCH, GPIO_Pin_RSet);
	GPIO_WritePin(GPIOA_Ptr, RS_SWITCH, GPIO_Pin_RSet);
	GPIO_WritePin(GPIOA_Ptr, RW_SWTICH, GPIO_Pin_RSet);
}

void LCD_Check_Lcd_isBusy()
{
	//DataDir_LCD_PORT &= ~(0xFF << DATA_shift);
	PinCfg.GPIO_Pin = GPIO_PIN_0;
	PinCfg.GPIO_Mode = GPIO_Mode_Input_FLO;
	GPIO_Init(GPIOA_Ptr, &PinCfg);

	PinCfg.GPIO_Pin = GPIO_PIN_1;
	PinCfg.GPIO_Mode = GPIO_Mode_Input_FLO;
	GPIO_Init(GPIOA_Ptr, &PinCfg);

	PinCfg.GPIO_Pin = GPIO_PIN_2;
	PinCfg.GPIO_Mode = GPIO_Mode_Input_FLO;
	GPIO_Init(GPIOA_Ptr, &PinCfg);

	PinCfg.GPIO_Pin = GPIO_PIN_3;
	PinCfg.GPIO_Mode = GPIO_Mode_Input_FLO;
	GPIO_Init(GPIOA_Ptr, &PinCfg);

	PinCfg.GPIO_Pin = GPIO_PIN_4;
	PinCfg.GPIO_Mode = GPIO_Mode_Input_FLO;
	GPIO_Init(GPIOA_Ptr, &PinCfg);

	PinCfg.GPIO_Pin = GPIO_PIN_5;
	PinCfg.GPIO_Mode = GPIO_Mode_Input_FLO;
	GPIO_Init(GPIOA_Ptr, &PinCfg);

	PinCfg.GPIO_Pin = GPIO_PIN_6;
	PinCfg.GPIO_Mode = GPIO_Mode_Input_FLO;
	GPIO_Init(GPIOA_Ptr, &PinCfg);

	PinCfg.GPIO_Pin = GPIO_PIN_7;
	PinCfg.GPIO_Mode = GPIO_Mode_Input_FLO;
	GPIO_Init(GPIOA_Ptr, &PinCfg);

	GPIO_WritePin(GPIOA_Ptr, RW_SWTICH, GPIO_Pin_Set);
	GPIO_WritePin(GPIOA_Ptr, RS_SWITCH, GPIO_Port_SRSet);
	//	GPIOA_Ptr |= (1 << RW_SWITCH);
	//	GPIOA_Ptr &= ~(1 << RS_SWITCH);
	LCD_lcd_Kick();
	//	DataDir_LCD_PORT |= (0xFF << DATA_shift);
	GPIO_WritePin(GPIOA_Ptr, RW_SWTICH, GPIO_Port_SRSet);
	//	GPIOA_Ptr &= ~(1 << RW_SWITCH);

}
/******************
APIS Implementation
 * ****************/

void LCD_Init (){
	delay_ms(20);
	LCD_GPIO_Init();
	//	GPIOA_Ptr &= ~(1 << EN_SWITCH | 1 << RS_SWITCH | 1 << RW_SWITCH);
	//	DataDir_LCD_PORT = 0xFF;
	delay_ms(15);
	clear_screen();
	LCD_Write_Command(LCD_FUNCTION_8BIT_2LINES);
	LCD_Write_Command(LCD_BEGIN_AT_FIRST_ROW);
	LCD_Write_Command(LCD_DISP_ON_CURSOR_BLINK);

}
void LCD_Write_Command (uint8_t command){
LCD_Check_Lcd_isBusy();
GPIO_WritePort(GPIOA_Ptr,command);
//	LCD_CTRL->BRR = (LCD_CTRL->BRR & 0x00FF) | (command);
//	LCD_CTRL->CRL ^= (LCD_CTRL->CRL ^ command) & 0x00ff;
//	LCD_CTRL->CRL = command;
//	LCD_CTRL ^= (LCD_CTRL-> ^ command) & 0x00ff;
GPIO_WritePin(GPIOA_Ptr, RW_SWTICH, GPIO_Pin_RSet);

GPIO_WritePin(GPIOA_Ptr, RS_SWITCH, GPIO_Pin_RSet);
//	LCD_CTRL &= ~((1 << RS_SWITCH) | (1<<RW_SWITCH));
delay_ms(1);
LCD_lcd_Kick();
}
void LCD_Write_Char(uint8_t character){
	//	LCD_check_lcd_isbusy();
	//	LCD_CTRL->CRL = character;
	//	LCD_CTRL->CRL ^= (LCD_CTRL->CRL ^ character) & 0x00ff;
	GPIO_WritePin(GPIOA_Ptr, RW_SWTICH, GPIO_Pin_RSet);

	GPIO_WritePin(GPIOA_Ptr, RS_SWITCH, GPIO_Pin_Set);
	//	LCD_CTRL &= ~(1 << RW_SWITCH);
	//	LCD_CTRL |= (1 << RS_SWITCH);
	delay_ms(1);
	LCD_lcd_Kick();

}
void LCD_Write_String (uint8_t* string){
	int count =0;
	while(*string >0)
	{
		count++;
		LCD_Write_Char(*string++);
			if(count ==16){
				LCD_GOTO_XY(2,0);
			}else if (count ==32){
				clear_screen();
				LCD_GOTO_XY(1,0);
				count =0;
			}
	}
}
void LCD_lcd_Kick(void){
	GPIO_WritePin(GPIOA_Ptr, EN_SWITCH, GPIO_Pin_Set);
	delay_ms(50);
	GPIO_WritePin(GPIOA_Ptr, EN_SWITCH, GPIO_Pin_RSet);


}
void clear_screen(){
	LCD_Write_Command(LCD_CLEAR_SCREEN);
}
void LCD_GOTO_XY(uint8_t Line, uint8_t position){
	if(Line ==1 ){
			if (position<16 && position >=0){
				LCD_Write_Command(LCD_BEGIN_AT_FIRST_ROW + position);

					}
	}
	if(Line ==2 ){
			if (position<16 && position >=0){
				LCD_Write_Command(LCD_BEGIN_AT_SECOND_ROW + position);

					}
	}

}
