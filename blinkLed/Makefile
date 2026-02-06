CC=avr-gcc
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
MCU_TARGET=atmega328p
OPTIMIZE=-Os
DEFS=
LIBS=

# Override is only needed by avr-lib build system.
override CFLAGS= -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

blinkLed.elf: blinkLed.o
	$(CC) $(CFLAGS) -o $@ $^

blinkLedInterrupt.elf: blinkLedInterrupt.o
	$(CC) $(CFLAGS) -o $@ $^

%.hex: %.elf 
	$(OBJCOPY) -j .text -j .data -O ihex $^ $@

.PHONY: clean mrproper

clean:
	rm -rf *.o *.hex *.elf

mrproper: clean
	rm -rf $(EXEC)
