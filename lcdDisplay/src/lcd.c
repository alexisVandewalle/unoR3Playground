#include "macro.h"
#include "lcd.h"
#include <util/delay.h>

void LCD_init(LcdIOSetup setup){
    // set portDB as output
#ifdef LCD_INTERFACE_4B
    *(setup.dirRegDB) = (*(setup.dirRegDB) & 0x0F) | 0xF0;
#else
    *(setup.dirRegDB) = 0xFF;
#endif
    // set output value
#ifdef LCD_INTERFACE_4B
    *(setup.portDB) = (*(setup.portDB) & 0x0F) | 0x0;
#else
    *(setup.portDB) = 0;
#endif
    // set port control as output (3 wire R/S R/W and Enable)
    *(setup.dirRegCtrl) |= 7 << setup.offsetCtrl;
    // set output value
    *(setup.portCtrl) &= ~(7 << setup.offsetCtrl);
    // set 8 bit interface
#ifdef LCD_INTERFACE_4B
    _delay_ms(15);
    LCD_write4Bits(setup, LCD_FUNCTION_SET|LCD_INTERFACE_8B, LCD_IR_REGISTER);
    _delay_ms(5);
    LCD_write4Bits(setup, LCD_FUNCTION_SET|LCD_INTERFACE_8B, LCD_IR_REGISTER);
    _delay_us(100);
    LCD_write4Bits(setup, LCD_FUNCTION_SET|LCD_INTERFACE_8B, LCD_IR_REGISTER);
    _delay_us(LCD_EXEC_DELAY_SHORT_US);
    LCD_write4Bits(setup, LCD_FUNCTION_SET|LCD_INTERFACE_4B, LCD_IR_REGISTER);
    _delay_us(LCD_EXEC_DELAY_SHORT_US);
    LCD_write(setup, LCD_FUNCTION_SET|LCD_INTERFACE_4B|LCD_DISPLAY_LINE_2|LCD_FONT_TYPE_SMALL, LCD_IR_REGISTER);
    _delay_us(LCD_EXEC_DELAY_SHORT_US);
#else
    _delay_ms(15);
    LCD_write(setup, LCD_FUNCTION_SET|LCD_INTERFACE_8B, LCD_IR_REGISTER);
    _delay_ms(5);
    LCD_write(setup, LCD_FUNCTION_SET|LCD_INTERFACE_8B, LCD_IR_REGISTER);
    _delay_us(100);
    LCD_write(setup, LCD_FUNCTION_SET|LCD_INTERFACE_8B, LCD_IR_REGISTER);
    _delay_us(LCD_EXEC_DELAY_SHORT_US);
    LCD_write(setup, LCD_FUNCTION_SET|LCD_INTERFACE_8B|LCD_DISPLAY_LINE_2|LCD_FONT_TYPE_SMALL, LCD_IR_REGISTER);
    _delay_us(LCD_EXEC_DELAY_SHORT_US);
#endif
    // display OFF
    LCD_displayOff(setup); 
    // clear display
    LCD_clear(setup); 
    // set entry mode
    LCD_write(setup, LCD_ENTRY_MODE_SET|LCD_MOVE_RIGHT, LCD_IR_REGISTER); 
    _delay_us(LCD_EXEC_DELAY_SHORT_US);
    // display ON
    LCD_displayOn(setup);
}


void LCD_write(LcdIOSetup setup, uint8_t data, uint8_t reg){
    *(setup.portCtrl) &= ~(7 << setup.offsetCtrl);
#ifdef LCD_INTERFACE_4B
    *(setup.portCtrl) |= reg | LCD_WRITE | LCD_ENABLE;
    *(setup.portDB) = (*(setup.portDB) & 0x0F) | (data & 0xF0);
    _delay_us(LCD_DELAY_US);

    *(setup.portCtrl) &= ~(7 << setup.offsetCtrl);
    _delay_us(LCD_DELAY_US);
    *(setup.portCtrl) |= reg | LCD_WRITE | LCD_ENABLE;
    *(setup.portDB) = (*(setup.portDB) & 0x0F) | (data << 4);
    _delay_us(LCD_DELAY_US);
#else 
    *(setup.portCtrl) |= reg | LCD_WRITE | LCD_ENABLE;
    *(setup.portDB) = data;
    _delay_us(LCD_DELAY_US);
#endif
    *(setup.portCtrl) &= ~(7 << setup.offsetCtrl);
    _delay_us(LCD_DELAY_US);
}

void LCD_write4Bits(LcdIOSetup setup, uint8_t data, uint8_t reg){
    *(setup.portCtrl) &= ~(7 << setup.offsetCtrl);

    *(setup.portCtrl) |= reg | LCD_WRITE | LCD_ENABLE;
    *(setup.portDB) = (*(setup.portDB) & 0x0F) | (data & 0xF0);
    _delay_us(LCD_DELAY_US);

    *(setup.portCtrl) &= ~(7 << setup.offsetCtrl);
    _delay_us(LCD_DELAY_US);
}

uint8_t LCD_read(LcdIOSetup setup, uint8_t reg){
    // set portDB as input / disable pull up
#ifdef LCD_INTERFACE_4B
    *(setup.dirRegDB) &= 0x0F;
    *(setup.portDB) &= 0x0F;
#else
    *(setup.dirRegDB) = 0;
    *(setup.portDB) = 0;
#endif

    *(setup.portCtrl) &= ~(7 << setup.offsetCtrl);
    *(setup.portCtrl) |= reg | LCD_READ | LCD_ENABLE;
    _delay_us(LCD_DELAY_US);
    *(setup.portCtrl) &= ~(7 << setup.offsetCtrl);
    _delay_us(LCD_DELAY_US);
#ifdef LCD_INTERFACE_4B
    uint8_t out = *(setup.pinDB) & 0xF0;
#else
    uint8_t out = *(setup.pinDB);
#endif

    // set portDB back as output
#ifdef LCD_INTERFACE_4B
    *(setup.dirRegDB) |= 0xF0;
    *(setup.portDB) &= 0x0F;
#else
    *(setup.dirRegDB) = 0xFF;
    *(setup.portDB) = 0;
#endif

    return out;
}

void LCD_writeStr(LcdIOSetup setup, char str[], uint8_t len, uint8_t startPos){
    LCD_write(setup, LCD_SET_DDRAM_ADDR|startPos, LCD_IR_REGISTER);
    _delay_us(LCD_EXEC_DELAY_SHORT_US);
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
            LCD_write(setup, LCD_SET_DDRAM_ADDR|startPos, LCD_IR_REGISTER);
            _delay_us(LCD_EXEC_DELAY_SHORT_US);
            continue;
        }
        LCD_write(setup, str[i], LCD_DR_REGISTER);
        _delay_us(LCD_EXEC_DELAY_SHORT_US);
        charIdxCurrentRow++;
    }
}

void LCD_clear(LcdIOSetup setup){
    LCD_write(setup, LCD_CLEAR_DISPLAY, LCD_IR_REGISTER); 
    _delay_ms(LCD_EXEC_DELAY_LONG_MS);
}

void LCD_cursorOn(LcdIOSetup setup){
    LCD_write(setup, LCD_ON_OFF_CTRL|LCD_DISP_ON|LCD_BLINK_ON|LCD_CURSOR_ON, LCD_IR_REGISTER);
    _delay_us(LCD_EXEC_DELAY_SHORT_US);
}

void LCD_cursorOff(LcdIOSetup setup){
    LCD_write(setup, LCD_ON_OFF_CTRL|LCD_DISP_ON|LCD_BLINK_OFF|LCD_CURSOR_OFF, LCD_IR_REGISTER);
    _delay_us(LCD_EXEC_DELAY_SHORT_US);
}

void LCD_displayOff(LcdIOSetup setup){
    LCD_write(setup, LCD_ON_OFF_CTRL|LCD_DISP_OFF, LCD_IR_REGISTER);
    _delay_us(LCD_EXEC_DELAY_SHORT_US);
}

void LCD_displayOn(LcdIOSetup setup){
    LCD_write(setup, LCD_ON_OFF_CTRL|LCD_DISP_ON, LCD_IR_REGISTER);
    _delay_us(LCD_EXEC_DELAY_SHORT_US);
}
