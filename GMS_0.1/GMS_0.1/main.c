/*
 * GMS_0.1.c
 *
 * Created: 4/11/2020 9:40:17 AM
 * Author : jbatt
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1<<DDB0);
	DDRB |= (1<<DDB1);
	
	while (1)
	{
		PORTB |= (1<<PORTB1);
		PORTB &= ~ (1<<PORTB0);
		_delay_ms(1000);
		PORTB &= ~ (1<<PORTB1);
		PORTB |= (1<<PORTB0);
		_delay_ms(500);	
	}
}


