#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define LED (1<<PB5)

int main() {
    int i = 0;

    DDRB |= LED;

    while (1) {
        i = 0;   // reset i

        while (i < 100) {
            PORTB |= LED;

            for(int j = 0; j < i; j++) {
                _delay_us(1);   // variable delay
            }

            PORTB &= ~LED;

            for(int j = 0; j < (100 - i); j++) {
                _delay_us(1);
            }

            i += 20;
        }
    }
    return 0;
}