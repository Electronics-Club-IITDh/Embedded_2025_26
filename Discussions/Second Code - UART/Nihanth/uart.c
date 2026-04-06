#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

void UART_Init(){
  //Configure the registers
  UBRR0=103; // Baud rate =9600bps
  UCSR0B|=(1<<RXEN0)|(1<<TXEN0);
  UCSR0C|=(1<<UCSZ00)|(1<<UCSZ01); //no need
}

void UART_Transmit(unsigned char ch){
  //Configure the registers
  while(!(UCSR0A & (1<<UDRE0))){ // masking,wait till it is empty (let prev byte is transmitted) 
  }
  UDR0=ch; // Transmit Buffer
}

unsigned char UART_Receive(){
  //Configure the registers
  
  // flag used is RXC0
  while((UCSR0A & (1<<RXC0))==0x00){ // wait till it recieves data (unread data), flag is set
  }
  return UDR0; // Recieve Buffer is read and flag is reset 
}

void UART_Transmit_string(unsigned char *str){
  while(*str){
  UART_Transmit(*str++);
  }
}

int main(){
  UART_Init();

  unsigned char str[100];
  uint8_t i;

  // Logic goes here
  while(1){
  UART_Transmit_string("Enter your name: \r\n");

  i=0;
  while(i<100){
    str[i]=UART_Recieve();
    if(str[i]=='\r') break;  // User Pressed Enter so it should stop receiving 
    i++;
  }
  str[i]='\0' // End of string

  UART_Transmit_String("\r\nHi! ");
  UART_Transmit_String(str);
  }

  return 0;
}

