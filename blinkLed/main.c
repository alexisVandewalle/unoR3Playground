#include <stdio.h>
#define F_CPU 16000000
#define F_TIMER0_CLOCK (F_CPU/1024)
#define MAX_COUNT 125
#define F_INTERRUPT_TIMER0 (F_TIMER0_CLOCK/MAX_COUNT)
#define PERIOD_INTERRUPT_TIMER0 (1000UL*MAX_COUNT/F_TIMER0_CLOCK)

int main(void){
    int period = PERIOD_INTERRUPT_TIMER0*11;
    printf("%d\n", period);
    return 0;
}
