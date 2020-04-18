/*
 * GMS_0.1.c
 *
 * Created: 4/11/2020 9:40:17 AM
 * Author : jbatt
 */ 

#define F_CPU 16000000UL
#define SERIAL_BAUD 9600
#define BRC ((F_CPU/16/SERIAL_BAUD) - 1)

#include <avr/io.h>
#include <util/delay.h>
#include "led.h"

int main(void)
{
	LED_Init();
	LED_PowerOn();

	while (1)
	{
		_delay_ms(1000);	
		LED_Status_Blink();
	}
}



