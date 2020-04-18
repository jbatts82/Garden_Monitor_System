/*
*******************************************************************************
      File Name  : led.c
      Author     : 
      Date       : 
      Description: 
 ******************************************************************************
 */

/*
 ******************************************************************************
 * INCLUDES
 ******************************************************************************
 */

#include "led.h"
#include <avr/io.h>

/*
 ******************************************************************************
 * DEFINES and CONSTANTS
 ******************************************************************************
 */


/*
 ******************************************************************************
 * GLOBAL VARIABLES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * LOCAL TYPES
 ******************************************************************************
 */

/*
 ******************************************************************************
 * LOCAL VARIABLES (declare as static)
 ******************************************************************************
 */



/*
 ******************************************************************************
 * LOCAL FUNCTION PROTOTYPES (declare as static)
 ******************************************************************************
 */



/*
 ******************************************************************************
 * GLOBAL FUNCTIONS
 ******************************************************************************
 */

/******************************************************************************
 * Function   : LED_PowerOn
 * Parameters : 
 * Return     : 
 * Description: 
******************************************************************************/
void LED_PowerOn(void)
{
	PORTB |= (1<<PORTB0);
}


void LED_Status_Blink(void)
{
	
	
}



/*
 ******************************************************************************
 * Local FUNCTIONS
 ******************************************************************************
 */

