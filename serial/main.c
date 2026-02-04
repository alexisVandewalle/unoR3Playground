#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define F_OSC 16e6f

int main(int argc, char* argv[]){

    int baudRate = atof(argv[1]);
    int ubrrVal = (int) roundf(F_OSC/(16.0f*((float)baudRate))-1.0f);
    printf("baud rate=%d\n", ubrrVal);
    printf("low bits=%d\n", ubrrVal & 0xFF);
    printf("high bits=%d\n", ubrrVal>>8);

    return 0;
}
