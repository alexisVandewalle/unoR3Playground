#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#define F_TIMER0_CLOCK (F_CPU/1024)
#define MAX_COUNT 125
#define N_CYCLE_TIMER0 (MAX_COUNT*1000UL)
#define PERIOD_INTERRUPT_TIMER0 (N_CYCLE_TIMER0/F_TIMER0_CLOCK)
#define TOOGLE_DELAY 1000

ISR(TIMER0_COMPA_vect){
    // static variable which count number of interruption on Timer0 compare match
    static int interruptCnt = 0;
    interruptCnt += 1;
    int currentDelayMs = interruptCnt*PERIOD_INTERRUPT_TIMER0;
    if(currentDelayMs > TOOGLE_DELAY){
        PORTB ^= _BV(PORTB5);
        interruptCnt = 0;
    }
}


int main(void){
    // disable interrupts
    cli();
    // set port B5 as output
    DDRB |= _BV(DDB5);
    PORTB &= ~_BV(PORTB5);
    // set timer 0 to CTC mode (compare and clear on match)
    TCCR0A |= (2 << WGM00);
    // set clock prescaler to 1024
    TCCR0B |= (0x5 << CS00); 
    // set max count for OCR0A
    OCR0A = MAX_COUNT;
    // enable interrupt
    TIMSK0 |= _BV(OCIE0A);
    sei();
    while(1){
    }
    return 0;
}
