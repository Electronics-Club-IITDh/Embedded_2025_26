#include<avr/io.h>
#include<util/delay.h>
#include<stdint.h>

void UART_Init()
{
  //Configure the registers
  UCSR0B |= (1<<RXEN0) | (1<<TXEN0);
  UBRR0   = 103;
}

void UART_Transmit(unsigned char c)
{
  //Configure the registers
  while((UCSR0A & (1<<UDRE0))==0x00);
  UDR0 = c;
}


unsigned char UART_Receive()
{
  //Configure the registers
  while((UCSR0A & (1<<RXC0))==0x00);
  return UDR0;
}

int main()
{
  UART_Init();

  //Blinking
  DDRB |= 0x20;

  //Dimming
  int i = 0, del = 0, f = 0,j = 0;
  DDRB = DDRB|(1<<DDB5);

  char input;

  while(1)
  {

    if((UCSR0A & (1<<RXC0))!=0x00) 
    {
      input = UART_Receive();
      // UART_Transmit(input);
    }

    if(input == 'B') {
        PORTB ^= 0x20;
        _delay_ms(500);
    }

    else if (input == 'D') {
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
  }