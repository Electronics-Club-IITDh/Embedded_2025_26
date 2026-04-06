#include<avr/io.h>
#include<stdint.h>
#include<util/delay.h>

int main()
{
  DDRB |= 0x20;
  while(1)
  {
    PORTB ^= 0x20;
    _delay_ms(500);
  }
  return 0;
}