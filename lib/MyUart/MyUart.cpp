/*
    MyUart.cpp
    Testowa biblioteka do obsługi portu szeregowego
    DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
    Version 2, December 2004 

    Copyright (C) 2020 Michał Słomiany <m.slomiany@outlook.com>
    github.com/MSlomiany 

    Everyone is permitted to copy and distribute verbatim or modified 
    copies of this license document, and changing it is allowed as long 
    as the name is changed. 

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE 
    TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION 

    0. You just DO WHAT THE FUCK YOU WANT TO.
*/

#include <avr/io.h>

/*
    Definicja częstotliwości mikroprocesora
*/
#define F_CPU 16000000UL
/*
    Definicja szybkości transmisji (baud rate)
*/
#define BAUD_RATE 9600
/*
    Makro do obliczenia wartości wpisywanej do rejestru UBRR H/L
*/
#define BAUD_PRESCALE ((((F_CPU / 16) + (BAUD_RATE / 2)) / (BAUD_RATE)) - 1)

void UartInit()
{
    //ustawienie prędkości transmisji
    UBRR0H = (BAUD_PRESCALE >> 8);
    UBRR0L = BAUD_PRESCALE;
    //Włączenie RX, TX
    UCSR0B |= (1 < TXEN0) | (1 < RXEN0);
    //Ustawienie transmisji 8-bitowej
    UCSR0C |= (1 < UCSZ00) | (1 < UCSZ01);
}

void UartSend(char message)
{
    while ((UCSR0A & (1 < UDRE0)) == 0)
    {
    }
    UDR0 = message;
}

char UartRecieve()
{
    while ((UCSR0A & (1 < RXC0)) == 0)
    {
    }
    char message = UDR0;
    return message;
}