#ifndef LCD_H_INCLUDED
#define LCD_H_INCLUDED

/*include avr/pgmspace.h so that when lcd.h is included in main,
main knows how the data type "prog_uchar" is defined*/
#include <avr/pgmspace.h>

//function prototypes
//check if lcd is ready
void lcd_ready(void);
//write a command byte to the lcd
void lcd_cmd(unsigned char cmd);
//write a data byte to the lcd
void lcd_data(unsigned char data);
//lcd initialization sequence
void lcd_init(void);
//reset lcd to initial state
void lcd_reset(void);
//lcd demo
void lcd_demo(void);
//write a sequence of characters to the lcd starting at the specified location
void lcd_print_string(const char* ptr, uint8_t num_chars, char loc);
//write a sequence of characters stored in flash memory to the lcd starting at the specified location
void lcd_print_string_progmem(const prog_uchar* ptr, uint8_t num_chars, char loc);
//write a number to the lcd
void lcd_print_num(uint16_t val, uint8_t num_digits, char loc);
//clear a specified portion of the lcd
void lcd_clear_segment(uint8_t num_segments, char loc);

#endif // LCD_H_INCLUDED
