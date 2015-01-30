#ifndef UART_H_INCLUDED
#define UART_H_INCLUDED

//libraries
#include <stdbool.h>

//constants
#define BAUDRATE 9600UL
#define UBRR_VAL (F_CPU/(16UL*BAUDRATE))-1

//function prototypes
//UART initialization sequence
void uart_init(void);
//check if input from UART is available
bool uart_available(void);
//read a character from the input buffer
unsigned char uart_read_char(void);
//check if a sequence of characters terminated by a newline character is available
//useful when accepting input from a keyboard via the serial port
bool uart_msg_available(void);
//read the incoming sequence of characters terminated by a newline character
void uart_read_msg(unsigned char* ptr);
//write a character to UART
void uart_write_char(unsigned char c);
//write a sequence of characters to UART
void uart_print_string(unsigned char* ptr);
//write a sequence of characters terminated by '/r'(carriage return) and '/n'(line feed) to UART
void uart_print_string_ln(unsigned char* ptr);
//write '\r' and '\n' to UART
void uart_crlf(void);
//flush UART input buffer
void uart_flush(void);

#endif /* UART_H_INCLUDED */
