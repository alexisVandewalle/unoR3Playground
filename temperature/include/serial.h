#ifndef SERIAL_H
#define SERIAL_H

void initUART(int baudRate);

void transmitUART(unsigned char data);

void transmitUARTStr(char string[]);
#endif
