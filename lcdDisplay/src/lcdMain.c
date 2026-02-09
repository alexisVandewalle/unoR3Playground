#define F_CPU 16000000UL
#include <avr/io.h>
#include "serial.h"
#include "lcd.h"

int main(void){
    LcdIOSetup setup = {
        &DDRD,
        &PORTD,
        &DDRB,
        &PORTB,
        0
    };
    LCD_initIO(setup);
    LCD_writeInstruction(setup);
    return 0;
}
