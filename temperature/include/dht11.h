// dht11.h
#ifndef DHT11_H
#define DHT11_H

#include "macro.h"

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

/**
 * Struct containing IO setup of DHT11 sensor
 */
typedef struct {
    volatile uint8_t* dirReg; // direction register address
    volatile uint8_t* portReg; // port register address
    volatile uint8_t* pinReg; // pin register address
    uint8_t pin; // pin value (use for all register)
} dht11IOSetup;

/**
 * Set timer 0 in normal mode and set prescale factor
 */
void dht11_configTimer();

/**
 * Send start signal to DHT11 sensor and configure data wire as input
 * @param setup variable containing IO setup of sensor 
 */
void dht11_sendStartSignal(dht11IOSetup setup);

/**
 * After start signal is sent, sensor start to output data. This function retrieves the data
 * and save it in temperature and humidity variable
 * @param setup variable containing IO setup of sensor 
 * @param tempI variable in which to store temperature integral part
 * @param tempD variable in which to store temperature decimal part
 * @param humidity variable in which to store humidity
 * @return 1 if data was succesfuly read, 0 if parity chek failed, 2 if a timeout occurs
 */
uint8_t dht11_getData(dht11IOSetup setup, uint8_t* tempI, uint8_t* tempD, uint8_t* humidity);

/**
 * Configure timer, send start signal and get data
 *
 * @param setup variable containing IO setup of sensor 
 * @param tempI variable in which to store temperature integral part
 * @param tempD variable in which to store temperature decimal part
 * @param humidity variable in which to store humidity
 * @return 1 if data was succesfuly read, 0 if parity chek failed, 2 if a timeout occurs
 */
uint8_t dht11_measure(dht11IOSetup setup, uint8_t* tempI, uint8_t* tempD, uint8_t* humidity);
#endif
