#include <avr/io.h>
#include <util/delay.h>
#include <math.h>
#define DATAOUT PB3      // MOSI
#define DATAIN  PB4      // MISO
#define SPICLOCK PB5     // SCK
#define CHIPSELECT PB2   // SS
#define ACK 0x06         // Acknowledge byte
#define NACK 0x15        // Not Acknowledge byte

void SPI_SlaveInit1(void) {
    DDRB = (1 << DATAIN);
    DDRB &= ~((1 << DATAOUT) | (1 << SPICLOCK) | (1 << CHIPSELECT));
    SPCR = (1 << SPE);
}

char spi_transfer1(char data) {
    SPDR = data;
    while (!(SPSR & (1 << SPIF)));
    return SPDR;
}

void setup1() {
    DDRB |= (1 << PB0);
    SPI_SlaveInit1();
}

void loop1() {
    static char received_data[2];
    static uint8_t received_index = 0;
    char result;
    char ack;

    if (SPSR & (1 << SPIF)) {
        received_data[received_index++] = SPDR;
        if (received_index >= 2) {
            received_index = 0;
            char x = received_data[0];
            char y = received_data[1];
            int valid = 1;

            switch (y) {
                case 0:
                    result = x + 1;
                    break;
                case 1:
                    result = x - 1;
                    break;
                case 2:
                    result = x * 2;
                    break;
                case 3:
                    result = floor(x / 3);
                    
                    break;
                default:
                    result = 0;
                    valid = 0;
                    break;
            }

            // Send ACK or NACK to Master
            if (valid ==1) {
                ack = ACK;
            } else {
                ack = NACK;
            }
            spi_transfer1(ack);

            if (valid == 1) {
                // Send the result back to Master
                PORTB &= ~(1 << CHIPSELECT);
                spi_transfer1(result);
                PORTB |= (1 << CHIPSELECT);
            }

            // Toggle built-in LED to indicate reception and processing
            PORTB ^= (1 << PB0);
            _delay_ms(1000);
        }
    }
}

int main(void) {
    setup1();
    while (1) {
        loop1();
    }
    return 0;
}
