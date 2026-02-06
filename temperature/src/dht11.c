#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#include "dht11.h"

void dht11_sendStartSignal(volatile uint8_t* dirReg, uint8_t dirRegBit, volatile uint8_t* port, char portBit){
    // set port D7 as output
    *dirReg |= _BV(dirRegBit);
    // pull down data wire
    *port &= ~_BV(portBit);
    // wait enough time before pulling data bus up
    _delay_ms(DHT11_START_SIG_DUR_MS);
    // set port as input
    *dirReg &= ~_BV(dirRegBit);
}

void dht11_configTimer(){
    // set timer 0 to normal mode
    TCCR0A = 0;
    // set timer 0 prescaler 
    TCCR0B = 3;
}

uint8_t dht11_getData(volatile uint8_t* dirReg, uint8_t dirRegBit, volatile uint8_t* pin, volatile uint8_t pinBit, uint8_t* temp, uint8_t* humidity){
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

uint8_t dht11_measure(
            volatile uint8_t* dirReg, uint8_t dirRegBit, 
            volatile uint8_t* port, char portBit,
            volatile uint8_t* pin, volatile uint8_t pinBit, 
            uint8_t* temp, uint8_t* humidity){
    dht11_configTimer();
    dht11_sendStartSignal(dirReg, dirRegBit, port, portBit);
    return dht11_getData(dirReg, dirRegBit, pin, pinBit, temp, humidity);
}
