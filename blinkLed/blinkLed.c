#include <avr/io.h>
#define F_CPU 16000000 // set CPU clock to 16MHz (used by _delay_ms)
#include <util/delay.h>

int main(void){
    // set PIN B5 as output
    DDRB |= _BV(DDB5);
    while(1){
        // set turn led on/off setting value of port B5
        PORTB ^= _BV(PORTB5);
        _delay_ms(1000);

    }
    return 0;
}
