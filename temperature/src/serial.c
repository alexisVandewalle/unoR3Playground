#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#define F_OSC 16e6f
#include <math.h>
#include "serial.h"

void initUART(int baudRate){
    // setting uart as asynchronous
    UCSR0C |= 0 << UMSEL00;
    UCSR0C &= ~_BV(UCPOL0);
    // setting of baud rate
    int ubrrVal = (int) roundf(F_OSC/(16.0f*((float)baudRate))-1.0f);
    UBRR0H = ubrrVal>>8;
    UBRR0L = (ubrrVal & 0xFF);
    // setting of frame format (8N1 8 bits-None parity-1 stop)
    // number of data bits (8 data bits)
    UCSR0B &= ~_BV(UCSZ02);
    UCSR0C |= 3 << UCSZ00;
    // number of stop bits
    UCSR0B &= ~_BV(USBS0);
    // parity check bit (no parity check)
    UCSR0C &= (~_BV(UPM00)) & (~_BV(UPM01));
    // enable receiver or transmitter
    UCSR0B |= _BV(TXEN0);
}

void transmitUART(unsigned char data){
    /* Wait for empty transmit buffer */
    while (!(UCSR0A & (1<<UDRE0)));
    UDR0 = data;
}

void transmitUARTStr(char string[]){
    int i=0; 
    while(string[i]!='\0'){
        transmitUART(string[i]); 
        i++;
    }
}
