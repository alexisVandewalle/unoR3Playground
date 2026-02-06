#ifndef SERIAL_H
#define SERIAL_H

/**Init serial communication setting up baud rate and frame format.
 * format 8bit None parity 1 stop bit is used
 */
void initUART(int baudRate);

/**
 * Transmit input data through UART
 */
void transmitUART(unsigned char data);

/**
 * Transmit input string through UART. '\0' indicate end of array
 */
void transmitUARTStr(char string[]);
#endif
