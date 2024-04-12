#ifndef DIO_INTERFACE_H
#define DIO_INTERFACE_H

typedef enum
{
	DIO_PORTA,DIO_PORTB,DIO_PORTC,DIO_PORTD
}Dio_Port_t;

typedef enum
{
	DIO_PIN0,
	DIO_PIN1,
	DIO_PIN2,
	DIO_PIN3,
	DIO_PIN4,
	DIO_PIN5,
	DIO_PIN6,
	DIO_PIN7
}Dio_Pin_t;


typedef enum
{
	DIO_PIN_LOW,
	DIO_PIN_HIGH
}Dio_PinVal_t;


typedef enum
{
	DIO_PIN_INPUT,
	DIO_PIN_OUTPUT
}Dio_PinDir_t;





uint8 DIO_u8SetPinDirection(Dio_Port_t copy_Port,Dio_Pin_t copy_PinNum,Dio_PinDir_t copy_PinDir);

uint8 DIO_u8SetPortDirection(Dio_Port_t copy_Port,uint8 copy_u8Port_Dir);


uint8 DIO_u8SetPinValue(Dio_Port_t copy_Port,Dio_Pin_t copy_PinNum,Dio_PinVal_t copy_Val);

uint8 DIO_u8SetPortValue(Dio_Port_t copy_Port,uint8 copy_u8Port_Val);

uint8 DIO_u8GetPinValue(Dio_Port_t copy_Port,Dio_Pin_t copy_PinNum,Dio_PinVal_t *copy_pVal);

uint8 Dio_u8TogglePin(Dio_Port_t copy_Port,Dio_Pin_t copy_PinNum);


#endif
