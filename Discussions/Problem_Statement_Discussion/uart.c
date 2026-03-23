#include<avr/io.h>
#include<util/delay.h>
#include<stdint.h>

void USART_Init()
{
  UBRR0 = 103;
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_Transmit( unsigned char data )
{
  while ( !( UCSR0A & (1<<UDRE0)) );
  UDR0 = data;
}

int main()
{
  char s[]="Hello\n\r\a";
  char c;
  uint8_t i=0;
  USART_Init();
  while(1)
  {
    c = s[0];
    while(c!='\0') 
    {
        USART_Transmit(c);
        c= s[++i];
        _delay_ms(100);
    }
    i=0;
  }
  return 0;
}