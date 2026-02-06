#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "serial.h"
#include <stdio.h>

#define DHT11_START_SIG_DUR_MS 18
#define DHT11_RESP_SIG_DUR_US 80
#define DHT11_DATA_SIG_DUR_US 50
#define DHT11_THRESHOLD_BIT_US 50
#define DHT11_N_BYTES 5
#define DHT11_N_BITS 40

#define F_IO_MHZ 16
#define TIMER0_PRESCALE_REG_SETUP 3
#define TIMER0_PRESCALE 64
#define TIMER0_STEP_US (TIMER0_PRESCALE/F_IO_MHZ)
#define DHT11_THRESHOLD_BIT (DHT11_THRESHOLD_BIT_US/TIMER0_STEP_US)
#define DHT11_TIMEOUT (100/TIMER0_STEP_US)
#define DHT11_TIMEOUT_CODE 2

void initio(){
    initUART(9600); 
}

void sendStartSignal(volatile uint8_t* dirReg, uint8_t dirRegBit, volatile uint8_t* port, char portBit){
    // set port D7 as output
    *dirReg |= _BV(dirRegBit);
    // pull down data wire
    *port &= ~_BV(portBit);
    // wait enough time before pulling data bus up
    _delay_ms(DHT11_START_SIG_DUR_MS);
    // set port as input
    *dirReg &= ~_BV(dirRegBit);
}

void configTimer(){
    // set timer 0 to normal mode
    TCCR0A = 0;
    // set timer 0 prescaler 
    TCCR0B = 3;
}

uint8_t getData(volatile uint8_t* dirReg, uint8_t dirRegBit, volatile uint8_t* pin, volatile uint8_t pinBit, uint8_t* temp, uint8_t* humidity){
    // wait response signal
    TCNT0 = 0;
    while((*pin & _BV(pinBit))){
        if(TCNT0>DHT11_TIMEOUT){
            return DHT11_TIMEOUT_CODE;
        }
    };
    // wait end of response signal
    TCNT0 = 0;
    while(!(*pin & _BV(pinBit))){
        if(TCNT0>DHT11_TIMEOUT){
            return DHT11_TIMEOUT_CODE;
        }
    }
    TCNT0 = 0;
    while((*pin & _BV(pinBit))){
        if(TCNT0>DHT11_TIMEOUT){
            return DHT11_TIMEOUT_CODE;
        }
    }

    uint8_t data[5] = {0};
    uint8_t idxData = 0;
    for(int8_t i=0; i<DHT11_N_BITS; i++){
        // wait start of bit transmission
        TCNT0 = 0;
        while(!(*pin & _BV(pinBit))){
            if(TCNT0>DHT11_TIMEOUT){
                return DHT11_TIMEOUT_CODE;
            }
        }
        // reset timer 0
        TCNT0 = 0;
        while((*pin & _BV(pinBit))){
            if(TCNT0>DHT11_TIMEOUT){
                return DHT11_TIMEOUT_CODE;
            }
        }
        data[idxData] <<= 1;
        data[idxData] |= (TCNT0 > DHT11_THRESHOLD_BIT); 
        if((i+1)%8==0){
            idxData++;
        }
    }
    // keep only integral part, decimal part not relevant
    // with respect to sensor accuracy
    *humidity = data[0];
    *temp = data[2];
    return (data[0]+data[1]+data[2]+data[3])==data[4];
}

int main(void){
    initUART(9600);
    configTimer();
    uint8_t temp, humidity;
    char buffer[100] = {'\0'};
    while(1){
        sendStartSignal(&DDRD, DDD7, &PORTD, PORTD7);
        uint8_t status = getData(&DDRD, DDD7, &PIND, PIND7, &temp, &humidity);
        sprintf(buffer, "T=%d H=%d status=%d\n", temp, humidity, status);
        transmitUARTStr(buffer);
        _delay_ms(10000);
    }
    return 0;
}
