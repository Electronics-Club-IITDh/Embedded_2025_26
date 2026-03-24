#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

int main(void)
{
  int i = 0, del = 0, f = 0,j = 0;
  DDRB = DDRB|(1<<DDB5);
  while(1)
  {
    for(i=1;i<=10;i++)
    {
      del = (int)((20/(0.1*i))-20);
      for(j=1;j<=2500;j++)
      {
        PORTB |=(1<<PORTB5);
        _delay_us(20);
        PORTB&=~(1<<PORTB5);
        for(f=1;f<=del;f++){
        _delay_us(1);
        } 
        _delay_us(1);
      }
    }

    for(i=10;i>=1;i--)
    {
      del = (int)((20/(0.1*i))-20);
      for(j=1;j<=2500;j++)
      {
        PORTB |=(1<<PORTB5);
        _delay_us(20);
        PORTB&=~(1<<PORTB5);
        for(f=1;f<=del;f++){
        _delay_us(1);
        } 
        _delay_us(1);
      }
    }

  }
}
