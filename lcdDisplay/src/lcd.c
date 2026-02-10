#include "lcd.h"
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <util/delay.h>

void LCD_init(LcdIOSetup setup){
    // set portDB as output
    *(setup.dirRegDB) = 0xFF;
    // set output value
    *(setup.portDB) = 0;
    // set port control as output (3 wire R/S R/W and Enable)
    *(setup.dirRegCtrl) |= 7 << setup.offsetCtrl;
    // set output value
    *(setup.portCtrl) &= ~(7 << setup.offsetCtrl);
    // set 8 bit interface
    LCD_write(setup, FUNCTION_SET|INTERFACE_8B|DISPLAY_LINE_2|FONT_TYPE_SMALL, IR_REGISTER);
    // display OFF
    LCD_write(setup, ON_OFF_CTRL|DISP_OFF, IR_REGISTER); 
    // clear display
    LCD_write(setup, CLEAR_DISPLAY, IR_REGISTER); 
    // set entry mode
    LCD_write(setup, ENTRY_MODE_SET|MOVE_RIGHT, IR_REGISTER); 
    // display ON
    LCD_write(setup, ON_OFF_CTRL|DISP_ON, IR_REGISTER); 
}


void LCD_write(LcdIOSetup setup, uint8_t data, uint8_t reg){
    *(setup.portCtrl) &= ~(7 << setup.offsetCtrl);
    *(setup.portCtrl) |= reg | LCD_WRITE | LCD_ENABLE;
    *(setup.portDB) = data;
    _delay_us(LCD_DELAY_US);
    *(setup.portCtrl) &= ~(7 << setup.offsetCtrl);
}

uint8_t LCD_read(LcdIOSetup setup, uint8_t reg){
    // set portDB as input / disable pull up
    *(setup.dirRegDB) = 0;
    *(setup.portDB) = 0;

    *(setup.portCtrl) &= ~(7 << setup.offsetCtrl);
    *(setup.portCtrl) |= reg | LCD_READ | LCD_ENABLE;
    _delay_us(LCD_DELAY_US);
    *(setup.portCtrl) &= ~(7 << setup.offsetCtrl);
    
    uint8_t out = *(setup.pinDB);

    // set portDB back as output
    *(setup.dirRegDB) = 0xFF;
    *(setup.portDB) = 0;

    return out;
}

void LCD_writeStr(LcdIOSetup setup, char str[], uint8_t len, uint8_t startPos){
    LCD_write(setup, SET_DDRAM_ADDR|startPos, IR_REGISTER);
    uint8_t offsetLine = startPos;
    if(startPos & 0xF0){
        offsetLine = offsetLine - LCD_ROW_2;
    }
    uint8_t charIdxCurrentRow = 0;
    for(uint8_t i=0; i<len; i++){
        if((offsetLine+charIdxCurrentRow)>=LCD_ROW_SIZE){
            break;
        }
        if(str[i]=='\n'){
            offsetLine = 0;
            startPos = LCD_ROW_2; 
            charIdxCurrentRow = 0;
            LCD_write(setup, SET_DDRAM_ADDR|startPos, IR_REGISTER);
            continue;
        }
        LCD_write(setup, str[i], DR_REGISTER);
        charIdxCurrentRow++;
    }
}

void LCD_clear(LcdIOSetup setup){
    LCD_write(setup, CLEAR_DISPLAY, IR_REGISTER); 
}

void LCD_cursorOn(LcdIOSetup setup){
    LCD_write(setup, ON_OFF_CTRL|DISP_ON|BLINK_ON|CURSOR_ON, IR_REGISTER);
}

void LCD_cursorOff(LcdIOSetup setup){
    LCD_write(setup, ON_OFF_CTRL|DISP_ON|BLINK_OFF|CURSOR_OFF, IR_REGISTER);
}

void LCD_displayOff(LcdIOSetup setup){
    LCD_write(setup, ON_OFF_CTRL|DISP_OFF, IR_REGISTER);
}

void LCD_displayOn(LcdIOSetup setup){
    LCD_write(setup, ON_OFF_CTRL|DISP_ON, IR_REGISTER);
}
