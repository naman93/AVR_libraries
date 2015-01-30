#ifndef RING_BUFFER_H_INCLUDED
#define RING_BUFFER_H_INCLUDED

//libraries
#include <stdbool.h>

//size of ring buffer
#define BUFFER_SIZE 50

//data structures
typedef struct
{
  unsigned char data[BUFFER_SIZE];
  unsigned char* head;
  unsigned char* tail;
}ring_buffer;

//function prototypes
//ring buffer initialization sequence
void ring_buffer_init(ring_buffer* buffer);
//check if ring buffer is empty
bool is_ring_buffer_empty(ring_buffer* buffer);
//check if ring buffer is full
bool is_ring_buffer_full(ring_buffer* buffer);
//write a data byte to the ring buffer
void ring_buffer_write(ring_buffer* buffer, unsigned char c);
//read a data byte from the ring buffer
unsigned char ring_buffer_read(ring_buffer* buffer);
//delete the newest byte in the ring buffer
void ring_buffer_delete(ring_buffer* buffer);
//clear the ring buffer
void ring_buffer_flush(ring_buffer* buffer);

#endif // RING_BUFFER_H_INCLUDED

