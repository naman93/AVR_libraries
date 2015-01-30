#ifndef LCD_PCD8544_H_INCLUDED
#define LCD_PCD8544_H_INCLUDED

//control pins
//RST - pin 1 on lcd (lcd reset pin)
#define RST_CONFIG DDRB
#define RST_PORT PORTB
#define RST_LOC PB1
//SCE - pin 2 on lcd (slave select pin)
#define SCE_CONFIG DDRB
#define SCE_PORT PORTB
#define SCE_LOC PB2
//D_C - pin 3 on lcd (data or command select pin)
#define D_C_CONFIG DDRB
#define D_C_PORT PORTB
#define D_C_LOC PB0
//DN - pin 4 on lcd (serial data pin)
#define DN_CONFIG DDRB
#define DN_PORT PORTB
#define DN_LOC PB3
//SCLK - pin 5 on lcd (clock input to lcd)
#define SCLK_CONFIG DDRB
#define SCLK_PORT PORTB
#define SCLK_LOC PB5

//delay to reset lcd
#define RST_DELAY 100
//lcd contrast (B0 to BF)
#define LCD_CONTRAST 0xBA

//lcd dimensions (vertical addressing)
#define NUM_ROWS 6
#define NUM_COLUMNS 84

//function protytypes
//write a command byte to lcd
void lcd_write_cmd(unsigned char cmd);
//write a data byte to lcd
void lcd_write_data(unsigned char cmd);
//lcd initialization sequence
void lcd_init(void);
//write local frame buffer to lcd memory
void lcd_update(void);
//clear(turn off) all pixels on the lcd
void lcd_clear(void);
//erase a specific line on the lcd
void lcd_clear_line(uint8_t index);
//write a character to the specified location in the frame buffer
void lcd_print_char(unsigned char c, uint8_t x_loc, uint8_t y_loc);
//write a string starting at a specified location in the frame buffer
void lcd_print_string(unsigned char* ptr, uint8_t x_loc, uint8_t y_loc);

#endif /* LCD_PCD8544_H_INCLUDED */
