#define F_CPU 16000000UL
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
    LCD_initIO(setup);
    // set 8 bit interface
    LCD_write(setup, FUNCTION_SET|INTERFACE_8B|DISPLAY_LINE_2|FONT_TYPE_SMALL, IR_REGISTER);
    _delay_ms(1000);
    // display OFF
    LCD_write(setup, ON_OFF_CTRL|DISP_OFF, IR_REGISTER); 
    _delay_ms(1000);
    // clear display
    LCD_write(setup, CLEAR_DISPLAY, IR_REGISTER); 
    _delay_ms(1000);
    // entry mode set
    LCD_write(setup, ENTRY_MODE_SET|MOVE_RIGHT, IR_REGISTER);
    _delay_ms(1000);
    // cursor or display shift
    // display ON
    LCD_write(setup, ON_OFF_CTRL|DISP_ON|BLINK_ON|CURSOR_ON, IR_REGISTER);
    _delay_ms(1000);
    // write character A at 0x01
    LCD_write(setup, SET_DDRAM_ADDR|0x01, IR_REGISTER);
    _delay_ms(1000);
    char text1[] = "hello";
    for(int i=0; i< 5; i++){
        LCD_write(setup, text1[i], DR_REGISTER);
        _delay_ms(1000);
    }
    // test screen off
    LCD_write(setup, ON_OFF_CTRL|DISP_OFF, IR_REGISTER); 
    _delay_ms(1000);
    // test screen on
    LCD_write(setup, ON_OFF_CTRL|DISP_ON, IR_REGISTER); 
    _delay_ms(1000);
    // test clear screen
    LCD_write(setup, CLEAR_DISPLAY, IR_REGISTER); 
    _delay_ms(1000);
    
    // write hello
    char text2[] = "12345";
    for(int i=0; i< 5; i++){
        LCD_write(setup, text2[i], DR_REGISTER);
        _delay_ms(1000);
    }
    // return home
    LCD_write(setup, RETURN_HOME, IR_REGISTER); 
    _delay_ms(1000);
    // write hello
    char text3[] = "ABCDE";
    for(int i=0; i< 5; i++){
        LCD_write(setup, text3[i], DR_REGISTER);
        _delay_ms(1000);
    }


    // test function to write str
    LCD_write(setup, CLEAR_DISPLAY, IR_REGISTER); 
    LCD_writeStr(setup, "test write", strlen("test write"), LCD_ROW_2);
    _delay_ms(2000);
    // test write str with too big input
    LCD_write(setup, CLEAR_DISPLAY, IR_REGISTER); 
    LCD_writeStr(setup, "test write too large gdsqfdjsqkl", strlen("test write too large gdsqfdjsqkl"), 0);
    _delay_ms(2000);
    // test write str on 2 rows
    LCD_write(setup, CLEAR_DISPLAY, IR_REGISTER); 
    LCD_writeStr(setup, "test write\non 2 rows", strlen("test write\non 2 rows"), 2);
    _delay_ms(2000);
    // test write str on 2 rows
    LCD_write(setup, CLEAR_DISPLAY, IR_REGISTER); 
    LCD_writeStr(setup, "test write\non 2 rows too large", strlen("test write\non 2 rows too large"), 2);
    _delay_ms(2000);
    



    while(1){
    }
    return 0;
}
