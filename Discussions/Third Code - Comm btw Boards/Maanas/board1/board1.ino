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
  char input;

  while(1)
  {

    input = UART_Receive();
    UART_Transmit(input);

  }
}