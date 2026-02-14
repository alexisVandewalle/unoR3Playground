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
    dht11IOSetup setup = {&DDRD, &PORTD, &PIND, PIND2};
    uint8_t tempI, tempD, humidity;
    char buffer[100] = {'\0'};
    while(1){
        uint8_t status = dht11_measure(setup, &tempI, &tempD, &humidity);
        sprintf(buffer, "T=%d.%d H=%d status=%d\n", tempI, tempD, humidity, status);
        transmitUARTStr(buffer);
        _delay_ms(5000);
    }
    return 0;
}
