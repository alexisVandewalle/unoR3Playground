// lcd.h
#ifndef LCD_H
#define LCD_H

#define CLEAR_DISPLAY 1
#define RETURN_HOME 2

// entry mode set
#define ENTRY_MODE_SET 4
#define MOVE_RIGHT 2 // no really usefull, better to use cursor_or_disp_shift
#define MOVE_LEFT 0
#define EN_SHIFT 1 // if enable the character are shifted at each insertion - cursor is fixed

// display ON/OFF control
#define ON_OFF_CTRL 8
#define DISP_ON 4
#define DISP_OFF 0
#define CURSOR_ON 2
#define CURSOR_OFF 0
#define BLINK_ON 1
#define BLINK_OFF 0

// cursor or display shift - usage not found for the moment
// #define CURSOR_OR_DISP_SHIFT 16
// #define CURSOR_MOVING 8
// #define CURSOR_FIX 0
// #define CURSOR_DIR_L 0 
// #define CURSOR_DIR_R 4

// function set
#define FUNCTION_SET 32
#define INTERFACE_8B 16
#define INTERFACE_4B 0
#define DISPLAY_LINE_2 8
#define DISPLAY_LINE_1 0
#define FONT_TYPE_BIG 4 // seems useless since characters still have same size
#define FONT_TYPE_SMALL 0

// set CGRAM address
#define SET_CGRAM_ADDR 64

// set DDRAM address
#define SET_DDRAM_ADDR 128

// write and read command
#define LCD_READ 1
#define LCD_WRITE 0

#define IR_REGISTER 0
#define DR_REGISTER 2
#define LCD_ENABLE (1 << 2)
#define LCD_DELAY_MS 2

// get busy flag and address after read command
#define LCD_getBusyFlag(reg) ((reg & 0x80)>>7)
#define LCD_getAddrCnt(reg) (reg & 0x7F)

#define LCD_ROW_SIZE 16
#define LCD_ROW_2 0x40

#include <stdint.h>

typedef struct{
    volatile uint8_t* dirRegDB;
    volatile uint8_t* portDB;
    volatile uint8_t* dirRegCtrl;
    volatile uint8_t* portCtrl;
    uint8_t offsetCtrl;
    volatile uint8_t* pinDB;
} LcdIOSetup;

void LCD_initIO(LcdIOSetup setup);

void LCD_write(LcdIOSetup setup, uint8_t data, uint8_t reg);

uint8_t LCD_read(LcdIOSetup setup, uint8_t reg);

void LCD_writeStr(LcdIOSetup setup, char str[], uint8_t len, uint8_t startPos);
#endif
