/*

 * main.c
 *calculator project using LCD and Keypad 4*4
 *  Created on: 5 Apr 2024
 *      Author: walid
 */

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_Type.h"
#include <util/delay.h>
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "KPD_interface.h"
#include "CLCD_interface.h"



void main(void)
{
	uint8 Local_u8Key=0xff;
	sint32 Local_s32Num1=0;
	sint32 Local_s32Num2=0;
	uint8 Local_u8Operation;

	sint32 Local_s32result=0;


	uint8 flag=0;
	PORT_voidIint();
	CLCD_voidInit();
	CLCD_u8SendString("Eid Moubarek");
	CLCD_voidGoToXY(0,1);
	CLCD_u8SendString("walid calculator");
	_delay_ms(2000);
	CLCD_voidSendCommand(1);
	while(1)
	{
		Local_u8Key=KPD_u8GetPressedKey();
		if(Local_u8Key!=0xff)
		{

			if(Local_u8Key>='0'&&Local_u8Key<='9')
			{

				if(flag==0)
				{   /*Clear the screen and set the cursor for the first time*/
					CLCD_voidGoToXY(0,0);
					CLCD_u8SendString("          ");
					CLCD_voidGoToXY(0,0);
					flag=1;
				}
				CLCD_voidSendData(Local_u8Key);
				Local_s32Num1=Local_s32Num1*10+(Local_u8Key-'0');// convert ascii number into decimal


			}
			if(Local_u8Key=='+'||Local_u8Key=='-'||Local_u8Key=='*'||Local_u8Key=='/')
			{
				if(flag==1)
				{
					CLCD_voidSendData(Local_u8Key);
					Local_s32Num2=Local_s32Num1;//save num1 in num2
					Local_s32Num1=0;//clear num 1 to save the second number
					Local_u8Operation=Local_u8Key;//save the choosed operation

				}
				if(flag==0)
				{


					CLCD_voidSendCommand(1);//clear the screen
					CLCD_voidSendNumber(Local_s32result);//display the result's operation
					CLCD_voidSendData(Local_u8Key);//display new operation on top
					Local_u8Operation=Local_u8Key;//save second operation
					flag=1;
				}


			}



			if(Local_u8Key=='=')
			{


				flag=0;
				CLCD_voidGoToXY(0,1);//move cursor to second line
				CLCD_u8SendString("                   ");// clear second line with some spaces
				CLCD_voidGoToXY(0,1);//move cursor to second line
				CLCD_voidSendData(Local_u8Key);//display = symbole

				Local_s32result=KPD_s32Calc(Local_u8Operation, Local_s32Num2,Local_s32Num1);// call KPD_s32Calc function and perform operation
				CLCD_voidGoToXY(1,1);
				Local_s32Num1=0;//reset num1
				Local_s32Num2=Local_s32result;//store the old result into num2 for the next operation on top



			}
			if(Local_u8Key=='c')//press c to reinitialise the calculator
			{
				CLCD_voidSendCommand(1);//clear screen
				Local_s32Num1=0;//reset number1
				Local_s32Num2=0;//rest number2
				Local_s32result=0;//reset result
			}

		}


	}
}
