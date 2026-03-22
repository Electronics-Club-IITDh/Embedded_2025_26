#include<avr/io.h>
#include<util/delay.h>
#include<stdint.h>

#define RINGPIN  (1<<6)
#define LED      (1<<7)

void sendOne()
{
  PORTB |= RINGPIN;
  _delay_us(1);
  PORTB &= ~RINGPIN;
}

void sendZero()
{
  PORTB |= RINGPIN;
  PORTB &= ~RINGPIN;
  _delay_us(1);
}

void sendLED(uint32_t g,uint32_t r,uint32_t b)
{
  uint8_t i;
  for(i=0;i<8;i++)
  {
    if((g&(1<<(8-i))) !=0) sendOne();
    else  sendZero();
  }
  for(i=0;i<8;i++)
  {
    if((r&(1<<(8-i))) !=0) sendOne();
    else  sendZero();
  }
  for(i=0;i<8;i++)
  {
    if((b&(1<<(8-i))) !=0) sendOne();
    else  sendZero();
  }

}

int main()
{
  DDRB |= RINGPIN | LED;
  uint8_t r,g,b,i,j,k,bright,time,offset;
  bright = 200;
  time = 20;
  offset = 0;
  while(1)
  {
    for(j=0;j<16;j++)
    {
        for(i=0;i<bright;i++)
        {
          for(k=0;k<16;k++)
          {
            if(j==k)
            {
              switch((j+offset)%3)
              {
                case 0: {r = i; g=0; b=0; break;}
                case 1: {g = i; r=0; b=0; break;}
                case 2: {b = i; g=0; r=0; break;}
              }
            }
            else {r=0; b=0; g=0;}
          sendLED(g,r,b);
          }
          PORTB |= LED;
          for(k=0;k<i;k++) _delay_us(time);
          PORTB &= ~LED;
          for(k=0;k<(bright-i);k++) _delay_us(time);
        }

        for(i=bright;i>0;i--)
        {
          for(k=0;k<16;k++)
          {
            if(j==k)
            {
              switch((j+offset)%3)
              {
                case 0: {r = i; g=0; b=0; break;}
                case 1: {g = i; r=0; b=0; break;}
                case 2: {b = i; g=0; r=0; break;}
              }
            }
            else {r=0; b=0; g=0;}
          sendLED(g,r,b);
          }
          PORTB |= LED;
          for(k=0;k<i;k++) _delay_us(time);
          PORTB &= ~LED;
          for(k=0;k<(bright-i);k++) _delay_us(time);
        }
      }
      offset = (offset+1)%3;
    }
  return 0;
}