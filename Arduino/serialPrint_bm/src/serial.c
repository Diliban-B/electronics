#include<avr/io.h>
#include<util/delay.h>
#include<string.h>

#define BAUD 9600
#define UBRR_VAL F_CPU/16/BAUD - 1 
#define BUFFER_SIZE 64

void uart_init(unsigned int ubrr){
    //Set Baud rate
    UBRR0H = (unsigned char) ubrr >> 8;
    UBRR0L = ubrr;

    // Enable Tx in UART
    UCSR0B = (1 << TXEN0) | (1 << RXEN0);

    UCSR0C = (1 << UCSZ00) | (1 << UCSZ01);

}

void uart_transmit(unsigned char data){
    while(!(UCSR0A & (1 << UDRE0)));

    UDR0 = data;
}

void uart_transmit_string(const char* str){
    while(*str){
        uart_transmit(*str++);
    }
}

unsigned char uart_receive(void){
    while(!(UCSR0A & (1 << RXC0)));

    return UDR0;
}

void uart_receive_string(char* buffer, char delim){
    char c;
    int i = 0;

    while(1){
        c = uart_receive();

        if(c == delim || i == BUFFER_SIZE - 1){
            buffer[i] = '\0';
            break;
        }

        buffer[i++] = c;
    }
}

int main(void){

    char buffer[BUFFER_SIZE], response[BUFFER_SIZE + 16];

    uart_init(UBRR_VAL);
    

    while (1)
    {
        uart_receive_string(buffer, '\n');

        strcpy(response, "Hello ");
        strcat(response, buffer);

        uart_transmit_string(response);
        uart_transmit_string("\r\n");

        _delay_ms(1000);
    }

    return 0;

}


