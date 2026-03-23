#include<avr/io.h>
#include<util/delay.h>
#include<stdint.h>

const char keypad[4][4] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

void USART_Init()
{
  UBRR0 = 103;
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void GPIO_Init()
{
  MCUCR   &= ~(1<<PUD);
  DDRC     = 0xF0;  //Rows output and Columns input
  PORTC   &= 0x0F;  //Rows given zero as output
  PORTC   |= 0x0F;  //Pull up the registers of input
}

void USART_Transmit( unsigned char data )
{
  while ( !( UCSR0A & (1<<UDRE0)) );
  UDR0 = data;
}

char detect_key()
{
  uint8_t row;

  for(row = 0; row < 4; row++)
  {
      PORTC |= 0xF0;                 
      PORTC &= ~(1 << (row+4));     
      _delay_us(10);                 

      if((PINC & 0x01) == 0) return keypad[row][0];
      else if((PINC & (1<<1)) == 0) return keypad[row][1];
      else if((PINC & (1<<2)) == 0) return keypad[row][2];
      else if((PINC & (1<<3)) == 0) return keypad[row][3];
  }

  return '\0';
}

int main()
{
  char key;

  USART_Init();
  GPIO_Init();

  while(1)
  {
    key = detect_key();

    if(key != '\0')
    {
      _delay_ms(20);   // debounce
      if(detect_key() == key)
      {
        USART_Transmit(key);
        USART_Transmit('\r');
        while(detect_key() != '\0'); // wait to release
      }
    }
  }
}