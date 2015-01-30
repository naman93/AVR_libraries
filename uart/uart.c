//standard libraries
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stddef.h>

//custom libraries
#include "ring_buffer.h"

//include header
#include "uart.h"

//global variables
//declare serial_in_buffer and msg_flag as static (not visible outside uart.c)
static ring_buffer serial_in_buffer;
static volatile uint8_t msg_flag = 0;

//ISR
//UART receive interrupt
ISR(USART_RX_vect)
{
	unsigned char c = UDR0;
	if(c == '\b')
	{
		//delete the previously received character if a backspace character is received
		ring_buffer_delete(&serial_in_buffer);
	}

	else
	{
		ring_buffer_write(&serial_in_buffer, c);
	}

	//set message flag if '\r' character is received
	if(c == '\r')
	{
		msg_flag = 1;
	}
}

//functions
//UART initialization sequence
void uart_init(void)
{
	//set the value of UBRR register to obtain desired baud rate
	UBRR0H =  (unsigned char) (UBRR_VAL >> 8);
	UBRR0L =  (unsigned char) UBRR_VAL;
	//enable receiver and transmitter
	UCSR0B |= ((1<<RXEN0) | (1<<TXEN0));
	//UMSEL01 = UMSEL00 = 0 (Asynchronous USART)
	//no parity UPM01 = UPM00 = 0
	//1 stop bit USBS0 = 0
	//character size (8 bit data) UCSZ01 = UCSZ00 = 1
	UCSR0C |= ((1<<UCSZ01) | (1<<UCSZ00));
	//enable receive interrupt
	UCSR0B |= (1<<RXCIE0);
	//initialize serial_in_buffer
	ring_buffer_init(&serial_in_buffer);

	//enable global interrupts
	sei();

	return;
}

//check if input from UART is available
bool uart_available(void)
{
	if(!is_ring_buffer_empty(&serial_in_buffer))
	{
		return (true);
	}

	else
	{
		return (false);
	}
}

//read a character from the input buffer
unsigned char uart_read_char(void)
{
	//if serial_in_buffer is not empty, return one character from the buffer
	if(!is_ring_buffer_empty(&serial_in_buffer))
	{
		return (ring_buffer_read(&serial_in_buffer));
	}

	else
	{
		//return NULL character
		return ('\0');
	}
}

//check if a sequence of characters terminated by a newline character is available
//useful when accepting input from a keyboard via the serial port
bool uart_msg_available(void)
{
	if(msg_flag == 1)
	{
		return (true);
	}

	else
	{
		return (false);
	}
}

//read the incoming sequence of characters terminated by a newline character
void uart_read_msg(unsigned char* ptr)
{
	unsigned char c = '\0';

	//read input characters until a '\r' character is reached or serial_in_buffer is empty
	while (uart_available())
	{
		if((c = uart_read_char()) != '\r')
		{
			*(ptr++) = c;
		}

		else
		{
			//finally add a '\0' at the end of the string
			*ptr = '\0';
			break;
		}
	}

	//reset msg_flag
	msg_flag = 0;

	return;
}

//write a character to UART
void uart_write_char(unsigned char c)
{
	//wait until data register is empty
	while(~UCSR0A & (1 << UDRE0));
	//write data to buffer
	UDR0 = c;

	return;
}

//write a sequence of characters to UART
void uart_print_string(unsigned char* ptr)
{
	if(ptr != NULL)
	{
		while(*ptr != '\0')
		{
			uart_write_char(*(ptr++));
		}
	}

	return;
}

//write a sequence of characters terminated by '/r'(carriage return) and '/n'(line feed) to UART
void uart_print_string_ln(unsigned char* ptr)
{
	if(ptr != NULL)
	{
		while(*ptr != '\0')
		{
			uart_write_char(*(ptr++));
		}

		//carriage return and line feed
		uart_crlf();
	}

	return;
}

//write '\r' and '\n' to UART
void uart_crlf(void)
{
	//carriage retutn
	uart_write_char('\r');
	//line feed
	uart_write_char('\n');

	return;
}

//flush UART input buffer
void uart_flush(void)
{
	ring_buffer_flush(&serial_in_buffer);

	return;
}
