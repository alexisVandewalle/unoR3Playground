# UNOR3 playground
# References

- avr-libc documentation: https://www.nongnu.org/avr-libc/user-manual
- avr-gcc documentation: https://gcc.gnu.org/wiki/avr-gcc#Using_avr-gcc
- avrdude documentation: https://avrdudes.github.io/avrdude/6.4/avrdude.html

# Compilation
- list targets: `avr-gcc --target-help`
- compile without linking (optimize for space recommended): `avr-gcc -mmcu=atmega328p -g -Os -c -o source.c`
- link and create `.elf` file: `avr-gcc -g -mmcu=atmega328p -o source.elf source.o`
- generate hex file (text and data section): `avr-objcopy -j .text -j .data -O ihex source.elf source.hex`
    - data section contains variable declared as global
    - text section contains the program
- write .hex file to flash: `avrdude -p m328p -e -U flash:w:filename`
