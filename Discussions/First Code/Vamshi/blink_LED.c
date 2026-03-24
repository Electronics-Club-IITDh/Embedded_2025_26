#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

int main(){

    DDRB |= (1 << DDB5);     // PB5 output (LED)

    DDRB &= ~(1 << DDB2);    // PB2 input
    PORTB |= (1 << PB2);     // enable internal pull-up
    _delay_us(100);
    while(1){

        if(!(PINB & (1 << PINB2))){   // pin HIGH (switch not pressed)
           // for(int i = 0; i < 10; i++){

                PORTB |= (1 << PB5);
                _delay_ms(1000);

                PORTB &= ~(1 << PB5);
                _delay_ms(1000);
            //}
        }
        else{   // pin HIGH (switch not pressed)
            //for(int i = 0; i < 10; i++){

                PORTB |= (1 << PB5);
                _delay_ms(100);

                PORTB &= ~(1 << PB5);
                _delay_ms(100);
            //}
        }
    }
}