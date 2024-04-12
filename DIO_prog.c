#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "Err_Type.h"


#include "DIO_interface.h"
#include "DIO_reg.h"




uint8 DIO_u8SetPinDirection(Dio_Port_t copy_Port,Dio_Pin_t copy_PinNum,Dio_PinDir_t copy_PinDir)
{
	uint8 Local_u8ErrorState=OK;
	if ((copy_PinNum>=DIO_PIN0 )&&  (copy_PinNum<=DIO_PIN7))
	{
		if(copy_PinDir==DIO_PIN_INPUT)
		{
			switch(copy_Port)
			{
			case DIO_PORTA:CLR_BIT(DDRA,copy_PinNum);break;
			case DIO_PORTB:CLR_BIT(DDRB,copy_PinNum);break;
			case DIO_PORTC:CLR_BIT(DDRC,copy_PinNum);break;
			case DIO_PORTD:CLR_BIT(DDRD,copy_PinNum);break;
			default: Local_u8ErrorState=NOK;break;
			}
		}
		else if (copy_PinDir==DIO_PIN_OUTPUT)
		{
			switch(copy_Port)
			{
			case DIO_PORTA:SET_BIT(DDRA,copy_PinNum);break;
			case DIO_PORTB:SET_BIT(DDRB,copy_PinNum);break;
			case DIO_PORTC:SET_BIT(DDRC,copy_PinNum);break;
			case DIO_PORTD:SET_BIT(DDRD,copy_PinNum);break;
			default: Local_u8ErrorState=NOK;break;
			}
		}
		else
		{
			Local_u8ErrorState=NOK;
		}
	}
	else
	{
		Local_u8ErrorState=NOK;
	}


	return Local_u8ErrorState;

}

uint8 DIO_u8SetPortDirection(Dio_Port_t copy_Port,uint8 copy_u8Port_Dir)
{

	uint8 Local_u8ErrorState=OK;

	switch(copy_Port)
	{
	case DIO_PORTA:DDRA=copy_u8Port_Dir;break;
	case DIO_PORTB:DDRB=copy_u8Port_Dir;break;
	case DIO_PORTC:DDRC=copy_u8Port_Dir;break;
	case DIO_PORTD:DDRD=copy_u8Port_Dir;break;
	default: Local_u8ErrorState=NOK;break;
	}


	return Local_u8ErrorState;
}


uint8 DIO_u8SetPinValue(Dio_Port_t copy_Port,Dio_Pin_t copy_PinNum,Dio_PinVal_t copy_Val)
{
	uint8 Local_u8ErrorState=OK;
	if ((copy_PinNum>=DIO_PIN0 )&&  (copy_PinNum<=DIO_PIN7))
	{
		if(copy_Val==DIO_PIN_LOW)
		{
			switch(copy_Port)
			{
			case DIO_PORTA:CLR_BIT(PORTA,copy_PinNum);break;
			case DIO_PORTB:CLR_BIT(PORTB,copy_PinNum);break;
			case DIO_PORTC:CLR_BIT(PORTC,copy_PinNum);break;
			case DIO_PORTD:CLR_BIT(PORTD,copy_PinNum);break;
			default: Local_u8ErrorState=NOK;break;
			}
		}
		else if (copy_Val==DIO_PIN_HIGH)
		{
			switch(copy_Port)
			{
			case DIO_PORTA:SET_BIT(PORTA,copy_PinNum);break;
			case DIO_PORTB:SET_BIT(PORTB,copy_PinNum);break;
			case DIO_PORTC:SET_BIT(PORTC,copy_PinNum);break;
			case DIO_PORTD:SET_BIT(PORTD,copy_PinNum);break;
			default: Local_u8ErrorState=NOK;break;
			}
		}
		else
		{
			Local_u8ErrorState=NOK;
		}
	}
	else
	{
		Local_u8ErrorState=NOK;
	}


	return Local_u8ErrorState;

}

uint8 DIO_u8SetPortValue(Dio_Port_t copy_Port,uint8 copy_u8Port_Val)
{

	uint8 Local_u8ErrorState=OK;
	switch(copy_Port)
	{
	case DIO_PORTA:PORTA=copy_u8Port_Val;break;
	case DIO_PORTB:PORTB=copy_u8Port_Val;break;
	case DIO_PORTC:PORTC=copy_u8Port_Val;break;
	case DIO_PORTD:PORTD=copy_u8Port_Val;break;
	default: Local_u8ErrorState=NOK;break;
	}


  return Local_u8ErrorState;

}

uint8 DIO_u8GetPinValue(Dio_Port_t copy_Port,Dio_Pin_t copy_PinNum,Dio_PinVal_t *copy_pVal)
{
	uint8 Local_u8ErrorState=OK;
	if(copy_pVal!=NULL)
	{
		if ((copy_PinNum>=DIO_PIN0 )&&  (copy_PinNum<=DIO_PIN7))
		{

	      switch(copy_Port)
		  {
		  case DIO_PORTA:*copy_pVal=GET_BIT(PINA,copy_PinNum);break;
		  case DIO_PORTB:*copy_pVal=GET_BIT(PINB,copy_PinNum);break;
		  case DIO_PORTC:*copy_pVal=GET_BIT(PINC,copy_PinNum);break;
		  case DIO_PORTD:*copy_pVal=GET_BIT(PIND,copy_PinNum);break;
		  default: Local_u8ErrorState=NOK;break;
		  }
		}
		else
		{
			Local_u8ErrorState=NOK;
		}

	}
	else
	{
		Local_u8ErrorState=NULL_PTR;
	}

	return Local_u8ErrorState;


}


uint8 Dio_u8TogglePin(Dio_Port_t copy_Port,Dio_Pin_t copy_PinNum)
{
	uint8 Local_u8ErrorState=OK;
	
if ((copy_PinNum>=DIO_PIN0 )&&  (copy_PinNum<=DIO_PIN7))
		{

	      switch(copy_Port)
		  {
		  case DIO_PORTA:TOG_BIT(PORTA,copy_PinNum);break;
		  case DIO_PORTB:TOG_BIT(PORTB,copy_PinNum);break;
		  case DIO_PORTC:TOG_BIT(PORTC,copy_PinNum);break;
		  case DIO_PORTD:TOG_BIT(PORTD,copy_PinNum);break;
		  default: Local_u8ErrorState=NOK;break;
		  }
		}
		else
		{
			Local_u8ErrorState=NOK;
		}
	
	
	
	
	
	return Local_u8ErrorState;
	
	
	
}