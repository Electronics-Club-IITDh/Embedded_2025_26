#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

/* --- Configuration --- */
#define FOSC 1843200   // Standard 16MHz clock for Arduino Uno/Nano
#define BAUD 9600            // Desired Baud Rate
#define MYUBRR 103

/* --- UART Functions --- */

void UART_Init(unsigned int ubrr) {
    // Set baud rate (High and Low registers)
  UBRR0H = (unsigned char)(ubrr>>8);
  UBRR0L = (unsigned char)ubrr;
  /* Enable receiver and transmitter */
  UCSR0B = (1<<RXEN0)|(1<<TXEN0);
  /* Set frame format: 8data, 2stop bit */
  UCSR0C = (3<<UCSZ00);
}

void UART_Transmit(unsigned char data) {
/* Wait for empty transmit buffer */
while ( !( UCSR0A & (1<<UDRE0)) )
//while((UCSR0A)&(1<<))
;
/* Put data into buffer, sends the data */
UDR0 = data;
}

unsigned char USART_Receive( void)
{
/* Wait for data to be received */
while ( !(UCSR0A & (1<<RXC0)) )// CHECKING WHETHER RECIEVE IS COPLETED OR NOT
;
/* Get and return received data from buffer */


return UDR0;
}

/* --- Main Program --- */

int main(void) {
  
    UART_Init(MYUBRR);

  char name[20];
  int i = 0;
  char c;

  while (1) {
    c = USART_Receive();   


    if (c == '\n') {

      name[i] = '\0';

      UART_Transmit('\r');
      UART_Transmit('H');
      UART_Transmit('i');
      UART_Transmit(' ');


      // print name
      for (int j = 0; name[j] != '\0'; j++) {
        UART_Transmit(name[j]);
      }

      UART_Transmit('\n');

      i = 0;   
    }
    else {
      name[i++] = c;
    }
  }
 return 0;
}