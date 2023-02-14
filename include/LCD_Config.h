#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_


/*Description: LCD data port configuration*/
/*Range: DIO_u8PortA ~ DIO_u8PortA*/
#define LCD_DATA_PORT 			MGPIO_PORTA

/*Description: LCD control port configuration*/
/*Range: DIO_u8PortA ~ DIO_u8PortA*/
#define LCD_CONTROL_PORT 		MGPIO_PORTC

#define 	LCD_RS_PIN 				PIN13
#define 	LCD_RW_PIN 				PIN15
#define 	LCD_E_PIN 				PIN14


#endif
