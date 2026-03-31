#include <avr/io.h>
#include <util/delay.h>

void UART_Init(){
  //Configure the registers
  UBRR0=103;
  UCSR0B|=(1<<RXEN0)|(1<<TXEN0);
  UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01); //no need
}

void UART_Transmit(){
  //Configure the registers
  while(!(UCSR0A & (1<<UDRE0))){ // masking wait till it is empty
  }
  UDR0='A';

}

unsigned char UART_Receive(){
  //Configure the registers
  while((UCSR0A & (1<<RXC0))==0x00){ // wait till it recieves completeley
  }
  return UDR0;
}

int main(){
  UART_Init();

  while(1){
  UART_Transmit();
  }

}

