#include "lcd.h"
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/io.h>

void LCD_initIO(LcdIOSetup setup){
   // set portDB as output
   *(setup.dirRegDB) = 0xFF;
   // set output value
   *(setup.portDB) = 0;
   // set port control as output (3 wire R/S R/W and Enable)
   *(setup.dirRegCtrl) = 7 << setup.offsetCtrl;
   // set output value
   *(setup.portCtrl) &= ~(7 << setupt.offsetCtrl);
}


void LCD_writeData(LcdIOSetup setup, uint8_t data){
   *(setup.portCtrl) &= ~(7 << setupt.offsetCtrl);
   *(setup.portCtrl) |= WRITE_TO_DR | ENABLE;
   *(setup.portDB) = data;
   _delay_ms(IR_DELAY_MS);
   *(setup.portCtrl) &= ~(7 << setupt.offsetCtrl);
}

void LCD_writeInstruction(LcdIOSetup setup, uint8_t instruction){
   *(setup.portCtrl) &= ~(7 << setupt.offsetCtrl);
   *(setup.portCtrl) |= WRITE_TO_IR | ENABLE;
   *(setup.portDB) = instruction;
   _delay_ms(IR_DELAY_MS);
   *(setup.portCtrl) &= ~(7 << setupt.offsetCtrl);
}

