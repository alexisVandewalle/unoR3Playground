#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include <stdio.h>
#include "serial.h"
#include "dht11.h"

void initio(){
    initUART(9600); 
}


int main(void){
    initUART(9600);
    uint8_t temp, humidity;
    char buffer[100] = {'\0'};
    while(1){
        uint8_t status = dht11_measure(&DDRD, DDD7,&PORTD, PORTD7, &PIND, PIND7, &temp, &humidity);
        sprintf(buffer, "T=%d H=%d status=%d\n", temp, humidity, status);
        transmitUARTStr(buffer);
        _delay_ms(10000);
    }
    return 0;
}
