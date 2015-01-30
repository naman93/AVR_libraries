#ifndef KEYPAD_H_INCLUDED
#define KEYPAD_H_INCLUDED

#define ROW 0
#define COL 1

//keypad state machine
#define MAYBE_PUSH 0
#define PUSH 1
#define MAYBE_NO_PUSH 2
#define NO_PUSH 3

//row pins
//row_0
#define ROW0_CONFIG DDRD
#define ROW0_PORT PORTD
#define ROW0_IN PIND
#define ROW0_LOC PD3
//row_1
#define ROW1_CONFIG DDRD
#define ROW1_PORT PORTD
#define ROW1_IN PIND
#define ROW1_LOC PD4
//row_2
#define ROW2_CONFIG DDRD
#define ROW2_PORT PORTD
#define ROW2_IN PIND
#define ROW2_LOC PD7
//row_3
#define ROW3_CONFIG DDRC
#define ROW3_PORT PORTC
#define ROW3_IN PINC
#define ROW3_LOC PC0
//column pins
//col_0
#define COL0_CONFIG DDRC
#define COL0_PORT PORTC
#define COL0_IN PINC
#define COL0_LOC PC1
//col_1
#define COL1_CONFIG DDRC
#define COL1_PORT PORTC
#define COL1_IN PINC
#define COL1_LOC PC2
//col_2
#define COL2_CONFIG DDRC
#define COL2_PORT PORTC
#define COL2_IN PINC
#define COL2_LOC PC3
//col_3
#define COL3_CONFIG DDRC
#define COL3_PORT PORTC
#define COL3_IN PINC
#define COL3_LOC PC4


//functions
//configure row pins as inputs and column pins as outputs
void row_in_col_out(void);
//configure column pins as inputs and row pins as outputs
void col_in_row_out(void);
//keypad initialization sequence
void keypad_init(void);
//checks the state of the row or column pins based on whether val = ROW or COL
//if a button is pressed, the bit corresponding to the row or column is set high
uint8_t get_keypad_pin_state(uint8_t val);
//check if any keypad events have been registered
bool is_keypad_event_available(void);
//read a keypad event (key code) from the buffer
unsigned char get_keypad_event(void);
//clear the buffer containing the keypad events
void keypad_event_flush(void);
//store a detected keypad event in the buffer
void store_keypad_event(uint8_t key_val_row, uint8_t key_val_col);
//scan the keypad to check if any key has been pressed
//this function must be called once every 30mS to update keypad state machine
void keypad_scan(void);


#endif /* KEYPAD_H_INCLUDED */
