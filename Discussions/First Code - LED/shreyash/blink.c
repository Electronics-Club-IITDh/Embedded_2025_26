#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define LED (1<<PB5) //DEFINR THE led port lless than the port 5

//LED output and ports are the input here the portB is the input in ardiuno always

int main() {
    int i = 0;
    // tells LED is output to ardiuno 
    DDRB |= LED;

    while (1) {
        i = 0;   

        while (i < 100) {
            PORTB |= LED;

            for(int j = 0; j < i; j++) {
                _delay_us(1);   
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