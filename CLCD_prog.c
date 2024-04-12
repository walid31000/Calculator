#include "STD_TYPES.h"
#include <util/delay.h>
#include "BIT_MATH.h"
#include "Err_Type.h"

#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "CLCD_prv.h"
#include "CLCD_cfg.h"

#if CLCD_u8CONNECTIO_MODE == FOUR_BIT
static void voidSetHalfDataPort(uint8 copy_u8FourBitData)
{
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D4_PIN, GET_BIT(copy_u8FourBitData,0));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D5_PIN, GET_BIT(copy_u8FourBitData,1));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D6_PIN, GET_BIT(copy_u8FourBitData,2));
	DIO_u8SetPinValue(CLCD_u8DATA_PORT,CLCD_u8D7_PIN, GET_BIT(copy_u8FourBitData,3));

}
#endif
static void void_SendEnablePulse(void)
{
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8E_PIN,DIO_PIN_HIGH);
	_delay_ms(2);
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8E_PIN,DIO_PIN_LOW);
}

void CLCD_voidSendCommand(uint8 copy_u8Command)
{
	/*1-SET RS pin to low for command*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RS_PIN,DIO_PIN_LOW);

	/*2-SET RW pin to low for write*/
#if CLCD_u8READ_OPERATION_ENABLE== ENABLED
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RW_PIN,DIO_PIN_LOW);
#endif
	/*3-Send the  command*/
#if CLCD_u8CONNECTIO_MODE == EIGHT_BIT
	DIO_u8SetPortValue(CLCD_u8DATA_PORT, copy_u8Command);


	/*4- send Enable pulse*/
	void_SendEnablePulse();
#elif CLCD_u8CONNECTIO_MODE == FOUR_BIT
	/*Send the higher 4 bit of the command*/
	voidSetHalfDataPort(copy_u8Command>>4u);
	/*4- send Enable pulse*/
	void_SendEnablePulse();
	/*Send the lower 4 bit of the command*/
	voidSetHalfDataPort(copy_u8Command);
	/*4- send Enable pulse*/
	void_SendEnablePulse();
#endif
}


void CLCD_voidSendData(uint8 copy_u8Data)
{
	/*1-SET RS pin to high for data*/
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RS_PIN,DIO_PIN_HIGH);

	/*2-SET RW pin to low for write*/
#if CLCD_u8READ_OPERATION_ENABLE== ENABLED
	DIO_u8SetPinValue(CLCD_u8CTRL_PORT,CLCD_u8RW_PIN,DIO_PIN_LOW);
#endif
	/*3-Send the  data*/
#if CLCD_u8CONNECTIO_MODE == EIGHT_BIT
	DIO_u8SetPortValue(CLCD_u8DATA_PORT,  copy_u8Data);


	/*4- send Enable pulse*/
	void_SendEnablePulse();
#elif CLCD_u8CONNECTIO_MODE == FOUR_BIT
	/*Send the higher 4 bit of the command*/
	voidSetHalfDataPort( copy_u8Data>>4u);
	/*4- send Enable pulse*/
	void_SendEnablePulse();
	/*Send the lower 4 bit of the command*/
	voidSetHalfDataPort( copy_u8Data);
	/*4- send Enable pulse*/
	void_SendEnablePulse();
#endif
}
void CLCD_voidInit (void)
{
	/*1-wait for more than 30sec after power on*/
	_delay_ms(40);

	/*2-Function Set command:2 lines ,font size :5*7*/
#if CLCD_u8CONNECTIO_MODE == EIGHT_BIT
	CLCD_voidSendCommand(0b00111000);
#elif CLCD_u8CONNECTIO_MODE ==FOUR_BIT
	voidSetHalfDataPort(0b0010);
	void_SendEnablePulse();
	voidSetHalfDataPort(0b0010);
	void_SendEnablePulse();
	voidSetHalfDataPort(0b1000);
	void_SendEnablePulse();
#endif
	/*3-Display on/off control display on,cursor off,blink off */
	CLCD_voidSendCommand(0b00001100);
	/*4-Display clear*/
	CLCD_voidSendCommand(1);

}

uint8 CLCD_u8SendString(const char *copy_u8String)
{
	uint8 Local_u8ErrorState=OK;

	if(copy_u8String!=NULL)

	{

		while(*copy_u8String!='\0')
		{
			CLCD_voidSendData(*copy_u8String);
			copy_u8String++;
		}

		/*uint8 Local_u8Counter=0u;
		while(copy_u8String[Local_u8Counter]!='\0')
		{
			CLCD_voidSendData(copy_u8String[Local_u8Counter]);
			Local_u8Counter++;
		}*/
	}
	else
	{
		return NULL_PTR;
	}

	return Local_u8ErrorState;

}


void CLCD_voidSendNumber (sint32 copy_s32Number)
{
	uint8 Local_u8conter1=0;
	char Local_chNumber [10];
	sint8  Local_s8conter2;
	if(copy_s32Number==0)
	{
		CLCD_voidSendData('0');
		return;
	}
	else if(copy_s32Number<0)
	{
		copy_s32Number*=-1;
		CLCD_voidSendData('-');

	}


	while (copy_s32Number)
	{
		Local_chNumber[Local_u8conter1++]=(uint8)((uint32)copy_s32Number%10+'0');/*convert number into ascii and save in in the array*/

		copy_s32Number/=10;/*get rid of the right digit */
	}


	for( Local_s8conter2= Local_u8conter1-1;Local_s8conter2>=0;Local_s8conter2--)
	{
		CLCD_voidSendData((uint8) Local_chNumber[Local_s8conter2]);
		//Local_u8conter--;
	}
}
void CLCD_voidGoToXY(uint8 copy_u8XPos,uint8 copy_u8Ypos)
{
	uint8 Local_u8DDRamAdd=(copy_u8Ypos*0x40)+copy_u8XPos;
	/*if(copy_u8YPos==0)
	 * {
	 * Local_u8DDRamAdd=copy_u8XPos;
	 * }
	 * else
	 * {
	 *  Local_u8DDRamAdd=0x40+copy_u8XPos;
	 * }
	 *
	 *
	 * */
	/*SET bit 7 for setting DDRAM adress command*/
	SET_BIT(Local_u8DDRamAdd,7u);
	/*send the setting DDRAM adress command*/
	CLCD_voidSendCommand(Local_u8DDRamAdd);

}

uint8 CLCD_u8WriteSpecialCharacter(uint8 copy_u8PatternNumber,uint8 copy_up8PatternArr[],uint8 copy_u8Xpos,uint8 copy_u8Ypos)
{
	uint8 Local_u8Errorstatus=OK;
	if(copy_up8PatternArr!=NULL)
	{
	 uint8 Local_u8CGRAMAdd=8* copy_u8PatternNumber;
	 uint8 Local_u8Iterator;
	 /*set CGRAM adress:set bit 6,clear bit 7*/
	 SET_BIT(Local_u8CGRAMAdd,6u);
	 /*SET CGRAM adress*/
	 CLCD_voidSendCommand(Local_u8CGRAMAdd);
	 /*write the pattern inside CGRAM*/
	 for(Local_u8Iterator=0;Local_u8Iterator<8;Local_u8Iterator++)
	 {
		 CLCD_voidSendData(copy_up8PatternArr[Local_u8Iterator]);

	  }
	 /*SET DDRAM adress*/
	 CLCD_voidGoToXY(copy_u8Xpos,copy_u8Ypos);

	/*write the corresponding pattern number to display from CGRAM*/
	CLCD_voidSendData(copy_u8PatternNumber);
	}
	else
	{
		return NULL_PTR;
	}

	return Local_u8Errorstatus;

}
