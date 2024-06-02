#include <avr/io.h>
#include <util/delay.h>


const uint8_t segment_map[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

void setup() {
    DDRB = 0xFF;
    DDRD = 0xFF;
}

void display_digit(uint8_t digit, uint8_t position) {
    PORTB = 0xFF;
    PORTD = segment_map[digit];
    PORTB = ~(1 << position);
    _delay_ms(5);
}

void display_number(uint8_t number) {
    uint8_t hundreds = (number / 100) % 10;
    uint8_t tens = (number / 10) % 10;
    uint8_t units = number % 10;

    for (int i = 0; i < 50; i++) {
        display_digit(hundreds, 2);
        display_digit(tens, 1);
        display_digit(units, 0);
    }
}

void loop() {
    static uint8_t a = 0, b = 1, next;

    next = a + b;
    if (next < a) {
        next = 0;
        a = 0;
        b = 1;
    } else {
        a = b;
        b = next;
    }

    display_number(next);

    _delay_ms(100);
}

int main(void) {
    setup();
    while (1) {
        loop();
    }
    return 0;
}
