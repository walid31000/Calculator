#include "STD_Types.h"
#include "Err_Type.h"

#include "DIO_interface.h"

#include "KPD_interface.h"
#include "KPD_prv.h"
#include "KPD_cfg.h"
#include "CLCD_interface.h"

uint8 KPD_u8GetPressedKey(void)
{
	uint8 Local_u8RowCounter,Local_u8ColCounter,Local_u8KeyState,Local_u8PressedKey=KPD_u8NO_PRESSED_KEY_VAL;

	static uint8 Local_u8ColArr[COL_NUM]={KPD_u8C0_PIN,KPD_u8C1_PIN,KPD_u8C2_PIN,KPD_u8C3_PIN};
	static uint8 Local_u8RowArr[ROW_NUM]={KPD_u8R0_PIN,KPD_u8R1_PIN,KPD_u8R2_PIN ,KPD_u8R3_PIN };
	static char Local_u8KPDArr[ROW_NUM][COL_NUM]=KPD_u8BUTTON_ARR;

	/*activate the column pins*/
	for(Local_u8ColCounter=0u;Local_u8ColCounter<COL_NUM ;Local_u8ColCounter++)
	{
		/*activate the current column*/
		DIO_u8SetPinValue(KPD_u8RCOL_PORT ,Local_u8ColArr[Local_u8ColCounter],DIO_PIN_LOW);

		/*Read the row pins*/

		for(Local_u8RowCounter=0u;Local_u8RowCounter<ROW_NUM;Local_u8RowCounter++)
		{
			/*Read the current Row*/
			DIO_u8GetPinValue(KPD_u8ROW_PORT ,Local_u8RowArr[Local_u8RowCounter],&Local_u8KeyState);
			if(Local_u8KeyState==DIO_PIN_LOW)
			{
				Local_u8PressedKey=Local_u8KPDArr[Local_u8RowCounter][Local_u8ColCounter];
				/*wait until key is released (polling with blocking on pin reading*/
				while(Local_u8KeyState==DIO_PIN_LOW)
				{
					DIO_u8GetPinValue(KPD_u8ROW_PORT ,Local_u8RowArr[Local_u8RowCounter],&Local_u8KeyState);
				}

				return Local_u8PressedKey;
			}
		}
		/*Deactivate the current column*/
		DIO_u8SetPinValue(KPD_u8RCOL_PORT,Local_u8ColArr[Local_u8ColCounter],DIO_PIN_HIGH);

	}
	return Local_u8PressedKey;
}


sint32 KPD_s32Calc(uint8 copy_u8Op,sint32 copy_s32Num1,sint32 copy_s32Num2)
{
	sint32 Local_s32Result=0;
	sint32 Local_s32ScaledResult;
	sint32 Local_s32Quotian;
	sint32 Local_S32Remainder;
	switch(copy_u8Op)
	{
	case '+': Local_s32Result=copy_s32Num1+copy_s32Num2;
	CLCD_voidSendNumber(Local_s32Result);break;

	case '-': Local_s32Result=copy_s32Num1-copy_s32Num2;
	CLCD_voidSendNumber(Local_s32Result);break;
	case '*': Local_s32Result=copy_s32Num1*copy_s32Num2;
	CLCD_voidSendNumber(Local_s32Result);break;
	case '/':if(copy_s32Num2!=0)
	{

		Local_s32ScaledResult=(copy_s32Num1*100)/copy_s32Num2;
		Local_s32Quotian=Local_s32ScaledResult/100;
		Local_S32Remainder=Local_s32ScaledResult%100;

		CLCD_voidSendNumber(Local_s32Quotian);
		CLCD_voidSendData('.');
		CLCD_voidSendNumber( Local_S32Remainder);

	}
	else
	{
		CLCD_u8SendString("No div by zero");
	}
	break;
	default:break;

	}

	return Local_s32Result;

}

