/*
 * source.c
 *
 *  Created on: 18 Mar 2024
 *      Author: Aly Ahmed
 */

#include"lcd.h"
#include"ultrasonic.h"
#include<avr/io.h>

#define ENABLE_INTERRUPTS()				(SREG|=(1<<7))

int main()
{
	ENABLE_INTERRUPTS();

	Ultrasonic_init();

	LCD_init();

	LCD_displayString("distance =");

	while(1)
	{

		Ultrasonic_readDistance();

		if (distance <100)
		{
			LCD_moveCursor(0, 11);
			LCD_integerToString(distance);
			LCD_displayCharacter(' ');
			LCD_displayString("Cm");

		}
		else
		{
			LCD_moveCursor(0, 11);
			LCD_integerToString(distance);
			LCD_displayString("Cm");
		}


	}

}
