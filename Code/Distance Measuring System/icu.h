/*
 * File Name: icu.h
 *
 * Created on: 15 Oct 2021
 *
 * Author: Aly Ahmed
 *
 * Description: Header File for ICU Driver
 *
 * Module: ICU
 *
 */


#ifndef ICU_H_
#define ICU_H_

#include "std_types.h"

/*********************************************************************************************************
 * 											Configurations
 *********************************************************************************************************/

typedef enum
{
	FALLING,RISING
}ICU_EDGE_TYPE;


typedef enum
{
	NO_CLOCK,CLK,CLK_8,CLK_64,CLK_256,CLK_1024
}ICU_CLOCK;


typedef struct
{
	ICU_EDGE_TYPE edge;
	ICU_CLOCK clk;
}ICU_configType;



/**********************************************************************************************************
 * 											Prototypes
 **********************************************************************************************************/


/*
 * Description: Function is used to initialize the ICU Driver by passing Structure of type Configuration
 * to it to configure the edge and the clock
 */
void ICU_init(ICU_configType *configtype);


/*
 * Description: Function Used to Set the Call Back
 */
void ICU_setupCallBack(void (*f_ptr)(void));



/*
 * Description: Function Used to detect the edge of the pulse
 */
void ICU_setEdgeDetectionType(const ICU_EDGE_TYPE edge_type);


/*
 * Description: Function used to get the value of the capture
 */
uint16 ICU_getInputCaptureValue(void);


/*
 * Description: Function to Clear the Timer Value
 */
void ICU_clearTimer(void);


/*
 * Description: Function To De-Initialize the ICU Driver
 */
void ICU_DeInit(void);


#endif /* ICU_H_ */
