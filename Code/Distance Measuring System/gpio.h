/*
 * [FILE NAME]		:		gpio.h
 *
 *
 * [AUTHOR]			:		Aly Ahmed
 *
 *
 * [FILE CREATED]	:		19/01/2024
 *
 *
 * [DESCRIPTION]	:		Header File that include the definitions and prototype of gpio for AVR
 *
 */

#ifndef GPIO_H_
#define GPIO_H_

#include"std_types.h"

/******************************************************************
 * 						Definitions
 *****************************************************************/

#define NUM_OF_PORTS				4
#define NUM_OF_PINS_PER_PORT		8


#define PORTA_ID					0
#define PORTB_ID					1
#define PORTC_ID					2
#define PORTD_ID					3


#define PIN0_ID						0
#define PIN1_ID						1
#define PIN2_ID						2
#define PIN3_ID						3
#define PIN4_ID						4
#define PIN5_ID						5
#define PIN6_ID						6
#define PIN7_ID						7


/******************************************************************
 * 						Types Deceleration
 ******************************************************************/

typedef enum
{
	PIN_INPUT,PIN_OUTPUT

}GPIO_PinDirectionType;


typedef enum
{
	PORT_INPUT,PORT_OUTPUT=0xFF

}GPIO_PortDirectionType;



/******************************************************************
 * 						Functions Prototypes
 ******************************************************************/


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

void GPIO_setupPinDirection(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType direction);




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

void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value);



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

uint8 GPIO_readPin(uint8 port_num, uint8 pin_num);



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

void GPIO_setupPortDirection(uint8 port_num, GPIO_PortDirectionType direction);



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

void GPIO_writePort(uint8 port_num, uint8 value);


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

uint8 GPIO_readPort(uint8 port_num);



#endif /* GPIO_H_ */
