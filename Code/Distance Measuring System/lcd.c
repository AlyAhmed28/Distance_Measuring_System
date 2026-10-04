/*
 * [FILE NAME]		:		lcd.c
 *
 *
 * [AUTHOR]			:		Aly Ahmed
 *
 *
 * [FILE CREATED]	:		22/01/2024
 *
 *
 * [DESCRIPTION]	:		Source File that include the Functions prototype of LCD driver for AVR
 *
 */

#include"lcd.h"
#include"gpio.h"
#include"common_macros.h"
#include"util/delay.h"



static void reverseString(uint8 *str);

/***********************************************************************
 * 							Functions Definitions
 **********************************************************************/


void LCD_init(void)
{

	GPIO_setupPinDirection(LCD_RW_PORT_ID, LCD_RW_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_RS_PORT_ID, LCD_RS_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_E_PORT_ID, LCD_E_PIN_ID, PIN_OUTPUT);

#if LCD_DATA_BITS_MODE == 4

	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_FIRST_DATA_PIN_ID, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_FIRST_DATA_PIN_ID+1, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_FIRST_DATA_PIN_ID+2, PIN_OUTPUT);
	GPIO_setupPinDirection(LCD_DATA_PORT_ID, LCD_FIRST_DATA_PIN_ID+3, PIN_OUTPUT);


	LCD_sendCommand(LCD_RETURN_HOME_COMMAND);
	LCD_sendCommand(LCD_TWO_LINE_4_BIT_MODE);

#elif LCD_DATA_BITS_MODE == 8
	GPIO_setupPortDirection(LCD_DATA_PORT_ID, PORT_OUTPUT);

	LCD_sendCommand(LCD_TWO_LINE_8_BIT_MODE);
#endif
	LCD_sendCommand(LCD_CLEAR_COMMAND);

	LCD_sendCommand(LCD_CURSOR_OFF_COMMAND);


}



void LCD_sendCommand(uint8 data)
{

	uint8 lcd_port_value = 0;

	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_LOW);
	GPIO_writePin(LCD_RW_PORT_ID, LCD_RW_PIN_ID, LOGIC_LOW);

	_delay_ms(1);

	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);

	_delay_ms(1);

#if LCD_DATA_BITS_MODE == 4

	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);

#ifdef LCD_LAST_PORT_PINS

	lcd_port_value =(lcd_port_value & 0x0F) | (data & 0xF0);
#else

	lcd_port_value = (lcd_port_value & 0xF0) | ((data & 0xF0)>>4);

#endif

	GPIO_writePort(LCD_DATA_PORT_ID, lcd_port_value);

	_delay_ms(1);

	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);
	_delay_ms(1);

	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);
	_delay_ms(1);

	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);

#ifdef LCD_LAST_PORT_PINS

	lcd_port_value = (lcd_port_value & 0x0F) | ((data & 0x0F)<<4);

#else

	lcd_port_value = (lcd_port_value & 0xF0) | (data & 0x0F);

#endif

	GPIO_writePort(LCD_DATA_PORT_ID, lcd_port_value);

	_delay_ms(1);

	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);

	_delay_ms(1);

#elif LCD_DATA_BITS_MODE == 8
	GPIO_writePort(LCD_DATA_PORT_ID, data);

	_delay_ms(1);

	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);

	_delay_ms(1);

#endif

}


void LCD_displayCharacter(uint8 character)
{

	uint8 lcd_port_value = 0;

	GPIO_writePin(LCD_RS_PORT_ID, LCD_RS_PIN_ID, LOGIC_HIGH);
	GPIO_writePin(LCD_RW_PORT_ID, LCD_RW_PIN_ID, LOGIC_LOW);

	_delay_ms(1);

	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);

	_delay_ms(1);

#if LCD_DATA_BITS_MODE == 4

	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);

#ifdef LCD_LAST_PORT_PINS

	lcd_port_value = (lcd_port_value & 0x0F) | (character & 0xF0);

#else

	lcd_port_value = (lcd_port_value & 0xF0) | ((character & 0xF0)>>4);

#endif

	GPIO_writePort(LCD_DATA_PORT_ID, lcd_port_value);

	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);

	_delay_ms(1);

	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_HIGH);

	_delay_ms(1);

	lcd_port_value = GPIO_readPort(LCD_DATA_PORT_ID);
#ifdef LCD_LAST_PORT_PINS

	lcd_port_value = (lcd_port_value & 0x0F) | ((character & 0x0F)<<4);

#else

	lcd_port_value = (lcd_port_value & 0xF0) | (character & 0x0F);

#endif

	GPIO_writePort(LCD_DATA_PORT_ID, lcd_port_value);

	_delay_ms(1);
	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);

	_delay_ms(1);


#elif LCD_DATA_BITS_MODE == 8
	GPIO_writePort(LCD_DATA_PORT_ID, character);

	_delay_ms(1);

	GPIO_writePin(LCD_E_PORT_ID, LCD_E_PIN_ID, LOGIC_LOW);

	_delay_ms(1);

#endif

}


void LCD_displayString(const uint8 *str)
{

	uint8 i=0;

	while(str[i] != '\0')
	{
		LCD_displayCharacter(str[i]);
		i++;
	}

}


void LCD_moveCursor(uint8 row, uint8 col)
{
	uint8 location;

	switch(row)
	{
		case 0:
			location = col;
			break;

		case 1:
			location = col+0x40;
			break;

		case 2:
			location = col+0x10;
			break;

		case 3:
			location = col+0x50;
			break;

	}

	LCD_sendCommand(location | LCD_SET_CURSOR_LOCATION);

}

void LCD_displayStringRowColumn(uint8 row, uint8 col, const uint8 *str)
{

	LCD_moveCursor(row, col);

	LCD_displayString(str);

}


void LCD_clearScreen(void)
{

	LCD_sendCommand(LCD_CLEAR_COMMAND);
}



void LCD_integerToString(int data)
{

	uint8 buff[20];

	uint8 reminder=0;
	uint8 i=0;

	if(data != 0)
	{
		while(data != 0)
		{
			reminder = data % 10;
			data /= 10;

			buff[i] = reminder +'0';

			i++;
		}

		buff[i] = '\0';

		reverseString(buff);

		LCD_displayString(buff);

		return;
	}

	if(data == 0)
	{
		buff[0] = '0';
		buff[1] = '\0';
		LCD_displayString(buff);
	}

}




static uint8 stringLength(const uint8 *str)
{
	uint8 count =0;
	uint8 i=0;

	while(str[i] != '\0')
	{
		count++;
		i++;
	}

	return count;
}

static void reverseString(uint8 *str)
{

	uint8 temp;
	uint8 i=0;
	uint8 j;

	j= stringLength(str) - 1;

	while(i<j)
	{

		temp = str[i];

		str[i] = str[j];

		str[j] = temp;

		i++;
		j--;
	}
}
