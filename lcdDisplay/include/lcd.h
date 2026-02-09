// lcd.h
#ifndef LCD_H
#define LCD_H

#define CLEAR_DISPLAY 1
#define RETURN_HOME 2

// entry mode set
#define ENTRY_MODE_SET 4
#define MOVE_FORWARD 2
#define MOVE_BACKWARD 0
#define EN_SHIFT 1

// display ON/OFF control
#define ON_OFF_CTRL 8
#define DISP_SHIFT_EN 4
#define CURSOR_EN 2
#define BLINK_EN 1

// cursor or display shift
#define CURSOR_OR_DISP_SHIFT 16
#define CURSOR_MOVING 8
#define CURSOR_DIR_L 4
#define CURSOR_DIR_R 0

// function set
#define FUNCTION_SET 32
#define INTERFACE_8B 16
#define INTERFACE_4B 0
#define DISPLAY_LINE_2 8
#define DISPLAY_LINE_1 0
#define FONT_TYPE_BIG 4
#define FONT_TYPE_SMALL 0

// set CGRAM address
#define SET_CGRAM_ADDR 64

// set DDRAM address
#define SET_DDRAM_ADDR 128

#define WRITE_TO_IR 0
#define WRITE_TO_DR 2
#define ENABLE (1 << 2)
#define IR_DELAY_MS 2

typedef struct{
    volatile uint8_t* dirRegDB;
    volatile uint8_t* portDB;
    volatile uint8_t* dirRegCtrl;
    volatile uint8_t* portCtrl;
    uint8_t offsetCtrl;
} LcdIOSetup;

void initDisplay();

void clearDisplay();
#endif
