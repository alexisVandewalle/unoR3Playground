CC=avr-gcc
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
MCU_TARGET=atmega328p
OPTIMIZE=-Os
DEFS=
LIBS=
BUILD_DIR=build

# Override is only needed by avr-lib build system.
override CFLAGS= -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS)

SRC=$(wildcard *.c)
OBJS=$(patsubst %.c, $(BUILD_DIR)/%.o, $(SRC))

$(BUILD_DIR)/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

serial.elf: $(OBJS)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $^

%.hex: %.elf 
	$(OBJCOPY) -j .text -j .data -O ihex $(BUILD_DIR)/$< $(BUILD_DIR)/$@

.PHONY: clean mrproper

clean:
	rm -rf $(BUILD_DIR)/*

mrproper: clean
	rm -rf $(EXEC)
