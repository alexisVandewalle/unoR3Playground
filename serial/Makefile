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

$(BUILD_DIR)/%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

$(BUILD_DIR)/serial.elf: $(BUILD_DIR)/serial.o
	$(CC) $(CFLAGS) -o $@ $^

%.hex: $(BUILD_DIR)/%.elf 
	$(OBJCOPY) -j .text -j .data -O ihex $^ $(BUILD_DIR)/$@

.PHONY: clean mrproper

clean:
	rm -rf $(BUILD_DIR)/*

mrproper: clean
	rm -rf $(EXEC)
