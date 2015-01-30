//standard libraries
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>

//custom libraries
#include "ring_buffer.h"

//include header
#include "keypad.h"

//global variables
//ring buffer to store keypad events
static ring_buffer key_event_buffer;
//stat of the keypad state machine
static uint8_t state = NO_PUSH;
//key lookup table
static unsigned char key_table[4][4] = {{'0','1','2','3'},
								  	  	{'4','5','6','7'},
								  	  	{'8','9','A','B'},
								  	  	{'C','D','E','F'}};

//functions
//configure row pins as inputs and column pins as outputs
void row_in_col_out(void)
{
	//disable pull up resistors for column input pins
	COL0_PORT &= ~(1<<COL0_LOC);
	COL1_PORT &= ~(1<<COL1_LOC);
	COL2_PORT &= ~(1<<COL2_LOC);
	COL3_PORT &= ~(1<<COL3_LOC);
	//set row pins as inputs
	ROW0_CONFIG &= ~(1<<ROW0_LOC);
	ROW1_CONFIG &= ~(1<<ROW1_LOC);
	ROW2_CONFIG &= ~(1<<ROW2_LOC);
	ROW3_CONFIG &= ~(1<<ROW3_LOC);
	//set column pins as outputs
	COL0_CONFIG |= (1<<COL0_LOC);
	COL1_CONFIG |= (1<<COL1_LOC);
	COL2_CONFIG |= (1<<COL2_LOC);
	COL3_CONFIG |= (1<<COL3_LOC);
	//enable pull up resistors for input(row) pins
	ROW0_PORT |= (1<<ROW0_LOC);
	ROW1_PORT |= (1<<ROW1_LOC);
	ROW2_PORT |= (1<<ROW2_LOC);
	ROW3_PORT |= (1<<ROW3_LOC);
	//wait for a certain time for the value on the input pin to reach a steady value
	//(RC charging time)
	_delay_us(5);
}

//configure column pins as inputs and row pins as outputs
void col_in_row_out(void)
{
	//disable pull up resistors for row input pins
	ROW0_PORT &= ~(1<<ROW0_LOC);
	ROW1_PORT &= ~(1<<ROW1_LOC);
	ROW2_PORT &= ~(1<<ROW2_LOC);
	ROW3_PORT &= ~(1<<ROW3_LOC);
	//set column pins as inputs
	COL0_CONFIG &= ~(1<<COL0_LOC);
	COL1_CONFIG &= ~(1<<COL1_LOC);
	COL2_CONFIG &= ~(1<<COL2_LOC);
	COL3_CONFIG &= ~(1<<COL3_LOC);
	//set row pins as outputs
	ROW0_CONFIG |= (1<<ROW0_LOC);
	ROW1_CONFIG |= (1<<ROW1_LOC);
	ROW2_CONFIG |= (1<<ROW2_LOC);
	ROW3_CONFIG |= (1<<ROW3_LOC);
	//enable pull up resistors for input(column) pins
	COL0_PORT |= (1<<COL0_LOC);
	COL1_PORT |= (1<<COL1_LOC);
	COL2_PORT |= (1<<COL2_LOC);
	COL3_PORT |= (1<<COL3_LOC);
	//wait for a certain time for the value on the input pin to reach a steady value
	//(RC charging time)
	_delay_us(5);
}

//keypad initialization sequence
void keypad_init(void)
{
	//set row pins as inputs and column pins as outputs
	row_in_col_out();
	//initialize key event buffer
	ring_buffer_init(&key_event_buffer);
}

//checks the state of the row or column pins based on whether val = ROW or COL
//if a button is pressed, the bit corresponding to the row or column is set high
uint8_t get_keypad_pin_state(uint8_t val)
{
	uint8_t ret_val = 0;

	if(val == ROW)
	{
		//assemble the nibble corresponding to the row pins
		ret_val |= ((ROW0_IN >> ROW0_LOC) & 0x01) << 0;
		ret_val |= ((ROW1_IN >> ROW1_LOC) & 0x01) << 1;
		ret_val |= ((ROW2_IN >> ROW2_LOC) & 0x01) << 2;
		ret_val |= ((ROW3_IN >> ROW3_LOC) & 0x01) << 3;
		//convert the nibble to active high and return it
		ret_val ^= 0x0F;

		return (ret_val);
	}

	else
	{
		//assemble the nibble corresponding to the column pins
		ret_val |= ((COL0_IN >> COL0_LOC) & 0x01) << 0;
		ret_val |= ((COL1_IN >> COL1_LOC) & 0x01) << 1;
		ret_val |= ((COL2_IN >> COL2_LOC) & 0x01) << 2;
		ret_val |= ((COL3_IN >> COL3_LOC) & 0x01) << 3;
		//convert the nibble to active high and return it
		ret_val ^= 0x0F;

		return (ret_val);
	}
}

//check if any keypad events have been registered
bool is_keypad_event_available(void)
{
	if(!is_ring_buffer_empty(&key_event_buffer))
	{
		return (true);
	}

	else
	{
		return (false);
	}
}

//read a keypad event (key code) from the buffer
unsigned char get_keypad_event(void)
{
	if(is_keypad_event_available())
	{
		return (ring_buffer_read(&key_event_buffer));
	}

	else
	{
		return ('\0');
	}
}

//clear the buffer containing the keypad events
void keypad_event_flush(void)
{
	ring_buffer_flush(&key_event_buffer);
}

//store a detected keypad event in the buffer
void store_keypad_event(uint8_t key_val_row, uint8_t key_val_col)
{
	//calculate row index and column index for key table
	uint8_t row_index = 0;
	uint8_t col_index = 0;

	switch(key_val_row)
	{
		case (0x01):
		{
			row_index = 0;
			break;
		}

		case (0x02):
		{
			row_index = 1;
			break;
		}

		case (0x04):
		{
			row_index = 2;
			break;
		}

		case (0x08):
		{
			row_index = 3;
			break;
		}
	}

	switch(key_val_col)
	{
		case (0x01):
		{
			col_index = 0;
			break;
		}

		case (0x02):
		{
			col_index = 1;
			break;
		}

		case (0x04):
		{
			col_index = 2;
			break;
		}

		case (0x08):
		{
			col_index = 3;
			break;
		}
	}

	//store the detected keypad event on the buffer
	ring_buffer_write(&key_event_buffer, key_table[row_index][col_index]);
}

//scan the keypad to check if any key has been pressed
//this function must be called once every 30mS to update keypad state machine
void keypad_scan(void)
{
	uint8_t key_val_row = get_keypad_pin_state(ROW);
	static uint8_t old_key_val_row = 0;
	static uint8_t old_key_val_col = 0;

	switch(state)
	{
		case NO_PUSH:
		{
			if(key_val_row == 0)
			{
				state = NO_PUSH;
			}

			else
			{
				state = MAYBE_PUSH;
			}

			break;
		}

		case MAYBE_PUSH:
		{
			if(key_val_row == 0)
			{
				state = NO_PUSH;
			}

			else
			{
				state = PUSH;
				old_key_val_row = key_val_row;
				//get input value for column
				col_in_row_out();
				old_key_val_col = get_keypad_pin_state(COL);
				//reset back to column output and row input
				row_in_col_out();
			}

			break;
		}

		case PUSH:
		{
			if(key_val_row == 0)
			{
				state = MAYBE_NO_PUSH;
			}

			else
			{
				state = PUSH;
			}

			break;
		}

		case MAYBE_NO_PUSH:
		{
			if(key_val_row == 0)
			{
				state = NO_PUSH;
				//button has been pushed and released
				//handle key event
				//save the code for the pressed key in the buffer (if valid)
				store_keypad_event(old_key_val_row, old_key_val_col);
			}

			else
			{
				state = PUSH;
			}

			break;
		}
	}
}


