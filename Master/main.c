#include <avr/io.h>
#include <util/delay.h>

#define DATAOUT 11  // MOSI
#define DATAIN  12  // MISO
#define SPICLOCK  13  // SCK
#define CHIPSELECT 10  // SS

void SPI_MasterInit(void) {
    DDRB = (1 << DATAOUT) | (1 << SPICLOCK) | (1 << CHIPSELECT);
    DDRB &= ~(1 << DATAIN);
  
    SPCR = (1 << SPE) | (1 << MSTR);
    
    PORTB |= (1 << CHIPSELECT);
}

char spi_transfer(char data) {
    SPDR = data;
  while (!(SPSR & (1 << SPIF))){
  PORTB ^= (1 << PB0);
    _delay_ms(500);
  };
    return SPDR;
}

void setup() {
    DDRB |= (1 << PB0);
    SPI_MasterInit();
}

void loop() {
    char x = 5; 
    char y = 1; 
    
    PORTB &= ~(1 << CHIPSELECT);
    spi_transfer(x);
    spi_transfer(y);
    PORTB |= (1 << CHIPSELECT);
    
   
    PORTB ^= (1 << PB0);
    // _delay_ms(500);
}

int main(void) {
    setup();
    while (1) {
        loop();
    }
    return 0;
}
