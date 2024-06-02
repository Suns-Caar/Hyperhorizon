#include <avr/io.h>
#include <util/delay.h>

void setup() {
    DDRD  = 0xFF; // Set PORTD as output for LED array
}


void display_number(uint8_t number) {
    PORTD = number; 
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

    _delay_ms(1500);  

}

int main(void) {
    setup();
    while (1) {
        loop();
    }
    return 0;
}
