/*
*******************************************************************************
      File Name  : serial.c
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

#include "serial.h"
#include "string.h"
#include "system_config.h"
#include <avr/io.h>
#include <avr/interrupt.h>


/*
 ******************************************************************************
 * DEFINES and CONSTANTS
 ******************************************************************************
 */

#define SERIAL_BAUD 9600
#define BRC ((F_CPU/16/SERIAL_BAUD) - 1)
#define TX_BUFFER_SIZE 128
#define RX_BUFFER_SIZE 128

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

static char tx_serial_buffer[TX_BUFFER_SIZE];
static uint8_t tx_serial_read_pos = 0;
static uint8_t serial_write_pos = 0;

static char rx_serial_buffer[RX_BUFFER_SIZE];
static uint8_t rx_serial_read_pos = 0;
static uint8_t rx_serial_write_pos = 0;


/*
 ******************************************************************************
 * LOCAL FUNCTION PROTOTYPES (declare as static)
 ******************************************************************************
 */

static void append_serial(char c);

/*
 ******************************************************************************
 * GLOBAL FUNCTIONS
 ******************************************************************************
 */

/******************************************************************************
 * Function   : SER_Init
 * Parameters : 
 * Return     : 
 * Description: 
******************************************************************************/
void SER_Init(void)
{
	/* Set Baud rate */
	/* Register doesn't take baud rate directly. */
	UBRR0H = (BRC >> 8);
	UBRR0L = BRC;
		
	/* Set Up Transmitter adn Rx*/
	UCSR0B = (1 << TXEN0) | (1 << TXCIE0) | (1 << RXEN0) | (1 << RXCIE0); 
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

/******************************************************************************
 * Function   : SER_Write
 * Parameters : 
 * Return     : 
 * Description: 
******************************************************************************/
void SER_Write(char c[])
{
	for(uint8_t i = 0; i < strlen(c); i++)
	{
		append_serial(c[i]);
	}
	
	//restart interrupt
	if(UCSR0A & (1 << UDRE0))
	{
		UDR0 = 0;
	}
}

char SER_Read_Char(void)
{
	char ret = "\0";
	if(rx_serial_read_pos != rx_serial_write_pos)
	{
		ret = rx_serial_buffer[rx_serial_read_pos];
		rx_serial_read_pos++;
	}
	return ret;
}

/*
 ******************************************************************************
 * Local FUNCTIONS
 ******************************************************************************
 */

/******************************************************************************
 * Function   : append_serial
 * Parameters : 
 * Return     : 
 * Description: 
******************************************************************************/
void append_serial(char c)
{
	tx_serial_buffer[serial_write_pos] = c;
	serial_write_pos++;
	if(serial_write_pos >= TX_BUFFER_SIZE)
	{
		serial_write_pos = 0;
	}
}



/******************************************************************************
 * Function   : 
 * Parameters : 
 * Return     : 
 * Description: 
******************************************************************************/
ISR(USART_TX_vect)
{
	if(tx_serial_read_pos != serial_write_pos)
	{
		UDR0 = tx_serial_buffer[tx_serial_read_pos];
		tx_serial_read_pos++;
		if(tx_serial_read_pos >= TX_BUFFER_SIZE)
		{
			tx_serial_read_pos++;
		}
	}
}

/******************************************************************************
 * Function   : 
 * Parameters : 
 * Return     : 
 * Description: 
******************************************************************************/
ISR(USART_RX_vect)
{
	rx_serial_buffer[rx_serial_write_pos] = UDR0;
	rx_serial_write_pos++;
	
	if(rx_serial_write_pos >= RX_BUFFER_SIZE)
	{
		rx_serial_write_pos = 0;
	}
}

char peekChar(void)
{
	char ret = "\0";
	
	if(rx_serial_read_pos != rx_serial_write_pos)
	{
		ret = rx_serial_buffer[rx_serial_read_pos];
	}
	
	return ret;
}

