#include "macro.h"
#include <util/delay.h>
#include <avr/io.h>
#include "serial.h"
#include "lcd.h"
#include <string.h>

int main(void){
    LcdIOSetup setup = {
        &DDRD,
        &PORTD,
        &DDRB,
        &PORTB,
        0,
        &PIND
    };
    _delay_ms(100);
    LCD_init(setup);
    while(1){
        LCD_writeStr(setup, "test write", strlen("test write"), 0);
        _delay_ms(1000);
        // test clear display
        LCD_clear(setup);
        // test write str on 2 rows
        LCD_writeStr(setup, "test write\non 2 rows too large", strlen("test write\non 2 rows too large"), 2);
        _delay_ms(1000);
        // test display off
        LCD_displayOff(setup);
        _delay_ms(1000);
        // test display on
        LCD_displayOn(setup);
         _delay_ms(1000);
        // test cursor
        LCD_clear(setup);
        LCD_writeStr(setup, "test cursor", strlen("test cursor"), 0);
        LCD_cursorOn(setup);
        _delay_ms(5000);
        LCD_cursorOff(setup);
        _delay_ms(1000); 
        LCD_clear(setup);
    }
    return 0;
}
