/*
    MyPort.cpp
    Testowa biblioteka do manipulacji portami
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
#include "MyPort.hpp"

/*
    Konstruktor nowego portu
    NewPort nazwa_portu(&PORTx, &DDRx, maska_bitowa)
*/
NewPort::NewPort(volatile uint8_t *port, volatile uint8_t *direction, uint8_t mask)
    : port_(port), direction_(direction), mask_(mask)
{
    //konstruktor
}

/*
    Konfiguracja portu jako wyjście
    nazwa_portu.output()
*/
void NewPort::output() const
{
    *direction_ |= mask_;
}

/*
    Konfiguracja portu jako wejście
    nazwa_portu.input()
*/
void NewPort::input() const
{
    uint8_t helpmask = (*direction_ & mask_);
    *direction_ ^= helpmask;
}

/*
    Ustawienie stanu wysokiego
    nazwa_portu.set()
*/
void NewPort::set() const
{
    *port_ |= mask_;
}

/*
    Ustawienie stanu niskiego
    nazwa_portu.clear()
*/
void NewPort::clear() const
{
    uint8_t helpmask = (*port_ & mask_);
    *port_ ^= helpmask;
}

/*
    Zmiana stanu na odwrotny
    nazwa_portu.invert()
*/
void NewPort::invert() const
{
    *port_ ^= mask_;
}
