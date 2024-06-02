# MCU and Programmer
MCU = atmega328p
PROGRAMMER = arduino
BAUD = 115200

# Paths and Files
TARGET = main
SRC = main.c
OBJ = $(SRC:.c=.o)

# Compiler and Flags
CC = avr-gcc
CFLAGS = -mmcu=$(MCU) -Os -DF_CPU=16000000UL

# AVRDUDE Flags
AVRDUDE = avrdude
AVRDUDE_FLAGS = -c $(PROGRAMMER) -p $(MCU) -b $(BAUD) -P /dev/ttyUSB0 -U flash:w:$(TARGET).hex

# Makefile Rules
all: $(TARGET).hex

$(TARGET).hex: $(TARGET).elf
	avr-objcopy -O ihex -R .eeprom $(TARGET).elf $(TARGET).hex

$(TARGET).elf: $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET).elf $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

upload: all
	$(AVRDUDE) $(AVRDUDE_FLAGS)

clean:
	rm -f $(TARGET).hex $(TARGET).elf $(OBJ)

.PHONY: all upload clean
