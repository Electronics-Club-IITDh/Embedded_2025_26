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

void UART_Transmit_string(unsigned char *s)
{
  while(*s)
  {
    UART_Transmit(*s++);
  }
}

int main()
{
  unsigned char s[101];
  uint8_t i;
  UART_Init();

  while(1)
  {
      //Logic goes here
      UART_Transmit_string("\r\nHello Guys! Welcome to my disgusting coding\r\n");
      i=0;
      while(i<100)
      {
          s[i++]=UART_Receive();
          UART_Transmit(s[i-1]);
          if(s[i-1]=='\r') break;
      }
      s[i]='\0';
      UART_Transmit_string("\r\nHi! ");
      UART_Transmit_string(s);
  }
}