/*
 * [FILE NAME]		:		gpio.c
 *
 *
 * [AUTHOR]			:		Aly Ahmed
 *
 *
 * [FILE CREATED]	:		19/01/2024
 *
 *
 * [DESCRIPTION]	:		Source File that include the Functions of gpio for AVR
 *
 */


#include<avr/io.h>
#include"gpio.h"
#include"common_macros.h"


/*
 * [FUNCTION NAME]		:	GPIO_setupPinDirection
 *
 * [INPUTS]				:	1- PORT_ID 		-> (PORTA_ID,PORTB_ID,PORTC_ID,PORTD_ID)
 * 						:	2- PIN_ID  		-> (PIN0_ID,PIN1_ID,PIN2_ID,PIN3_ID,.....etc)
 * 						:	3- PinDirection -> (PIN_Input or PIN_Output)
 *
 *
 * [DESCRIPTION]		:	this function used to setup pin direction if it is input/output
 * 							if the input of pin number or port number not correct the function will not
 * 							handle the request
 */

void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction)
{

		/*
		 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
		 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
		 * In this case the input is not valid port/pin number
		 */

	if( (port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT) )
	{
		/* do nothing */
	}

	else
	{
		/* Setup pin direction */
		switch(port_num)
		{
			case PORTA_ID:

				if(direction == PIN_OUTPUT)
				{
					SET_BIT(DDRA,pin_num);
				}
				else
				{
					CLEAR_BIT(DDRA,pin_num);
				}
				break;

			case PORTB_ID:

				if(direction == PIN_OUTPUT)
				{
					SET_BIT(DDRB,pin_num);
				}
				else
				{
					CLEAR_BIT(DDRB,pin_num);
				}
				break;

			case PORTC_ID:

				if(direction == PIN_OUTPUT)
				{
					SET_BIT(DDRC,pin_num);
				}
				else
				{
					CLEAR_BIT(DDRC,pin_num);
				}
				break;

			case PORTD_ID:

				if(direction == PIN_OUTPUT)
				{
					SET_BIT(DDRD,pin_num);
				}
				else
				{
					CLEAR_BIT(DDRD,pin_num);
				}
				break;

		}


	}

}


/*
 * [FUNCTION NAME]		:	GPIO_writePin
 *
 * [INPUTS]				:	1- PORT_ID -> (PORTA_ID,PORTB_ID,PORTC_ID,PORTD_ID)
 * 						:	2- PIN_ID  -> (PIN0_ID,PIN1_ID,PIN2_ID........etc)
 * 						:	3- value   -> (LOGIC_HIGH or LOGIC_LOW)
 *
 * [DESCRIPTION]		:	this function is used to write logic high (1) or logic low (0) on the required
 * 							pin in port, if the input port number or pin number is not correct the function
 * 							will not handle the request, and if the pin is input this function will
 * 							enable/disable the internal pull-up resistor
 *
 */

void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value)
{

	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */

	if( (port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT) )
	{
		/* do nothing */
	}

	/* Write on the required pin */
	else
	{
		switch(port_num)
		{
			case PORTA_ID:

				if(value == LOGIC_HIGH)
				{
					SET_BIT(PORTA,pin_num);
				}
				else
				{
					CLEAR_BIT(PORTA,pin_num);
				}
				break;

			case PORTB_ID:

				if(value == LOGIC_HIGH)
				{
					SET_BIT(PORTB,pin_num);
				}
				else
				{
					CLEAR_BIT(PORTB,pin_num);
				}
				break;

			case PORTC_ID:

				if(value == LOGIC_HIGH)
				{
					SET_BIT(PORTC,pin_num);
				}
				else
				{
					CLEAR_BIT(PORTC,pin_num);
				}
				break;

			case PORTD_ID:

				if(value == LOGIC_HIGH)
				{
					SET_BIT(PORTD,pin_num);

				}
				else
				{
					CLEAR_BIT(PORTD,pin_num);
				}
				break;
		}

	}
}


/*
 * [FUNCTION NAME]			:	GPIO_readPin
 *
 * [INPUTS]					:	1-	PORT_ID -> (PORTA_ID,PORTB,ID,PORTC_ID,PORTD_ID)
 * 							:	2-	PIN_ID  -> (PIN0_ID, PIN1_ID, PIN2_ID,......etc)
 *
 * [RETURN VALUE]			:	value on the required pin which is LOGIC_HIGH (1) or LOGIC_LOW (0)
 *
 *
 * [DESCRIPTION]			:	read and return the value for the required pin, it should be LOGIC_HIGH
 * 								or LOGIC_LOW.
 * 								if the input port number or pin number are not correct, the function will
 * 								return LOGIC_LOW
 */

uint8 GPIO_readPin(uint8 port_num, uint8 pin_num)
{

	/* variable to hold the read value of the required pin */
	uint8 read_pin = LOGIC_LOW;


	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */

	if( (port_num >= NUM_OF_PORTS) || (pin_num >= NUM_OF_PINS_PER_PORT) )
	{
		read_pin = LOGIC_LOW;
	}

	else
	{
		/* read from the required pin number */
		switch(port_num)
		{
			case PORTA_ID:

				if(BIT_IS_SET(PINA,pin_num))
				{
					read_pin = LOGIC_HIGH;
				}

				else
				{
					read_pin = LOGIC_LOW;
				}
				break;

			case PORTB_ID:

				if(BIT_IS_SET(PINB,pin_num))
				{
					read_pin = LOGIC_HIGH;
				}

				else
				{
					read_pin = LOGIC_LOW;
				}
				break;

			case PORTC_ID:

				if(BIT_IS_SET(PINC,pin_num))
				{
					read_pin = LOGIC_HIGH;
				}

				else
				{
					read_pin = LOGIC_LOW;
				}
				break;

			case PORTD_ID:

				if(BIT_IS_SET(PIND,pin_num))
				{
					read_pin = LOGIC_HIGH;
				}

				else
				{
					read_pin = LOGIC_LOW;
				}
				break;
		}
	}


	/* return the value of pin*/
	return read_pin;

}



/*
 * [FUNCTION NAME]		:	GPIO_setupPortDirection
 *
 * [INPUTS]				:	1- PORT_ID 		-> (PORTA_ID,PORTB_ID,PORTC_ID,PORTD_ID)
 * 						:	2- PortDirection -> (PORT_INPUT or PORT_OUTPUT)
 *
 *
 * [DESCRIPTION]		:	this function used to setup port direction if it is PORT_INPUT/PORT_OUTPUT
 * 							if the input port number not correct the function will not
 * 							handle the request
 */

void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction)
{

	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port number
	 */

	if(port_num >= NUM_OF_PORTS)
	{
		/* do nothing */
	}

	/* setup PORT direction */
	else
	{
		switch(port_num)
		{
			case PORTA_ID:

				DDRA = direction;
				break;

			case PORTB_ID:

				DDRB = direction;
				break;

			case PORTC_ID:

				DDRC = direction;
				break;

			case PORTD_ID:

				DDRD = direction;
				break;
		}
	}

}


/*
 * [FUNCTION NAME]		:	GPIO_writePort
 *
 *
 * [INPUTS]				:	1- PORT_ID -> (PORTA_ID, PORTB_ID, PORTC_ID, PORTD_ID)
 * 						:	2- value   -> (the value that will be write on the port (all the pins) )
 *
 * [DESCRIPTION]		:	write the value on the required port.
 * 						:	if any pin in the port is output pin the value will be written
 * 						:	if any pin in the port is input pin this will activate/deactivate the internal
 * 							pull-up resistor.
 * 						:	if the input port number is not correct, the function will not handle request.
 */

void GPIO_writePort(uint8 port_num, uint8 value)
{

	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port number
	 */

	if(port_num >= NUM_OF_PORTS)
	{
		/* do nothing */
	}


	else
	{
		/* write on the required port */
		switch(port_num)
		{
			case PORTA_ID:

				PORTA = value;
				break;

			case PORTB_ID:

				PORTB = value;
				break;

			case PORTC_ID:

				PORTC = value;
				break;

			case PORTD_ID:

				PORTD = value;
				break;
		}
	}

}


/*
 * [FUNCTION NAME]			:	GPIO_readPort
 *
 * [INPUTS]					:	PORT_ID -> (PORTA_ID,PORTB,ID,PORTC_ID,PORTD_ID)
 *
 * [RETURN VALUE]			:	value on the required port which is LOGIC_HIGH (1) or LOGIC_LOW (0)
 *
 *
 * [DESCRIPTION]			:	read and return the value for the required port, it should be LOGIC_HIGH
 * 								or LOGIC_LOW.
 * 								if the input port number not correct, the function will
 * 								return LOGIC_LOW
 */

uint8 GPIO_readPort(uint8 port_num)
{

	/* Variable to hold the value of the required port */
	uint8 read_port = LOGIC_LOW;


	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */

	if(port_num >= NUM_OF_PORTS)
	{
		read_port = LOGIC_LOW;
	}

	else
	{

		/* read the port value */
		switch(port_num)
		{
			case PORTA_ID:

				if(PINA == LOGIC_HIGH)
				{
					read_port = LOGIC_HIGH;
				}
				else
				{
					read_port = LOGIC_LOW;
				}
				break;

			case PORTB_ID:

				if(PINB == LOGIC_HIGH)
				{
					read_port = LOGIC_HIGH;
				}
				else
				{
					read_port = LOGIC_LOW;
				}
				break;

			case PORTC_ID:

				if(PINC == LOGIC_HIGH)
				{
					read_port = LOGIC_HIGH;
				}
				else
				{
					read_port = LOGIC_LOW;
				}
				break;

			case PORTD_ID:

				if(PIND == LOGIC_HIGH)
				{
					read_port = LOGIC_HIGH;
				}
				else
				{
					read_port = LOGIC_LOW;
				}
				break;
		}
	}

	return read_port;
}
