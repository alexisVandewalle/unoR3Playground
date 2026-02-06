// dht11.h
#ifndef DHT11_H
#define DHT11_H

#define DHT11_START_SIG_DUR_MS 18
#define DHT11_RESP_SIG_DUR_US 80
#define DHT11_DATA_SIG_DUR_US 50
#define DHT11_THRESHOLD_BIT_US 50
#define DHT11_N_BYTES 5
#define DHT11_N_BITS 40

#define F_IO_MHZ (F_CPU/1000000UL)
#define TIMER0_PRESCALE_REG_SETUP 3
#define TIMER0_PRESCALE 64
#define TIMER0_STEP_US (TIMER0_PRESCALE/F_IO_MHZ)
#define DHT11_THRESHOLD_BIT (DHT11_THRESHOLD_BIT_US/TIMER0_STEP_US)
#define DHT11_TIMEOUT (100/TIMER0_STEP_US)
#define DHT11_TIMEOUT_CODE 2

void dht11_configTimer();
void dht11_sendStartSignal(volatile uint8_t* dirReg, uint8_t dirRegBit, volatile uint8_t* port, char portBit);
uint8_t dht11_getData(volatile uint8_t* dirReg, uint8_t dirRegBit, volatile uint8_t* pin, volatile uint8_t pinBit, uint8_t* temp, uint8_t* humidity);
uint8_t dht11_measure(
            volatile uint8_t* dirReg, uint8_t dirRegBit, 
            volatile uint8_t* port, char portBit,
            volatile uint8_t* pin, volatile uint8_t pinBit, 
            uint8_t* temp, uint8_t* humidity);
#endif
