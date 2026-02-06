CC=avr-gcc
OBJCOPY=avr-objcopy
OBJDUMP=avr-objdump
MCU_TARGET=atmega328p
OPTIMIZE=-Os
DEFS=
LIBS=
BUILD_DIR=build
SRC_DIR=src
INCLUDE_DIR=include

# Override is only needed by avr-lib build system.
override CFLAGS= -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) $(DEFS) -I $(INCLUDE_DIR)

SRCS=$(wildcard $(SRC_DIR)/*.c)
OBJS=$(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

%.elf: $(OBJS)
	$(CC) $(CFLAGS) -o $(BUILD_DIR)/$@ $^

%.hex: %.elf 
	$(OBJCOPY) -j .text -j .data -O ihex $(BUILD_DIR)/$< $(BUILD_DIR)/$@

all: temperature.hex
	echo "build targets done"	

.PHONY: clean mrproper

clean:
	rm -rf $(BUILD_DIR)/*

mrproper: clean
	rm -rf $(EXEC)

.SECONDARY:
