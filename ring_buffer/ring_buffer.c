//include header
#include "ring_buffer.h"

//functions
//ring buffer initialization sequence
void ring_buffer_init(ring_buffer* buffer)
{
    //initialize head and tail to point to the first element in data array
    buffer->head = buffer->data;
    buffer->tail = buffer->data;

    return;
}

//check if ring buffer is empty
bool is_ring_buffer_empty(ring_buffer* buffer)
{
    //buffer is empty if head and tail pointers point to the same location in data array
    if(buffer->head == buffer->tail)
    {
        return (true);
    }

    else
    {
        return (false);
    }
}

//check if ring buffer is full
bool is_ring_buffer_full(ring_buffer* buffer)
{
    //conditions for which buffer is full
    //head points to one element before tail in data array or
    //head points to the last element and tail points to the first element in data array
    if(((buffer->tail)-(buffer->head) == 1) || (((buffer->head) - (buffer->tail)) == BUFFER_SIZE-1))
    {
        return (true);
    }

    else
    {
        return (false);
    }
}

//write a data byte to the ring buffer
void ring_buffer_write(ring_buffer* buffer, unsigned char c)
{
	// Note:- if buffer is full, oldest data will be overwritten in circular manner!!!
	//store incoming data
	*(buffer->head) = c;

	if(!is_ring_buffer_full(buffer))
	{
		//ring_buffer is not full
		//update only head pointer of the buffer
		//if head points to the last element in the buffer,
		//then make it point to the first element
		if(buffer->head == &(buffer->data)[BUFFER_SIZE-1])
		{
			buffer->head = &(buffer->data)[0];
		}
		//else make head point to the next element
		else
		{
			buffer->head++;
		}
	}

	else
	{
		//ring_buffer is full
		//update both head and tail pointer of the buffer
		//update of tail pointer implies that the oldest character in the buffer is deleted

		//if head points to the last element in the buffer,
		//then make it point to the first element
		if(buffer->head == &(buffer->data)[BUFFER_SIZE-1])
		{
			buffer->head = &(buffer->data)[0];
		}
		//else make head point to the next element
		else
		{
			buffer->head++;
		}

		//if tail points to the last element in the buffer,
		//then make it point to the first element
		if(buffer->tail == &(buffer->data)[BUFFER_SIZE-1])
		{
			buffer->tail = &(buffer->data)[0];
		}
		//else make tail point to the next element
		else
		{
			buffer->tail++;
		}
	}

	return;
}

//read a data byte from the ring buffer
unsigned char ring_buffer_read(ring_buffer* buffer)
{
    if(!is_ring_buffer_empty(buffer))
    {
        unsigned char return_char = *(buffer->tail);
        //update tail pointer
        //if tail pointer points to the last element then make it point to the first element
        if(buffer->tail == &(buffer->data)[BUFFER_SIZE-1])
        {
            buffer->tail = &(buffer->data)[0];
        }
        //else make tail pointer point to the next element
        else
        {
            buffer->tail++;
        }

        return (return_char);
    }

    else
    {
        //if buffer is empty return a NULL character
        return ('\0');
    }
}

//delete the newest byte in the ring buffer
void ring_buffer_delete(ring_buffer* buffer)
{
	//if ring buffer is not empty, point head to previous position in ring buffer
	if(!is_ring_buffer_empty(buffer))
	{
		if(buffer->head == &(buffer->data)[0])
		{
			buffer->head == &(buffer->data)[BUFFER_SIZE-1];
		}

		else
		{
			buffer->head--;
		}
	}

	return;
}

//clear the ring buffer
void ring_buffer_flush(ring_buffer* buffer)
{
	//make head and tail point to the same location in the buffer
	buffer->tail = buffer->head;

	return;
}
