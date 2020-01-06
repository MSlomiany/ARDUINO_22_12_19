/*
    MyPort.hpp
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
//definicja pliku nagłówkowego
#ifndef MyPort_hpp
#define MyPort_hpp
//biblioteki systemowe
#include <avr/io.h>

class NewPort
{
public:
    NewPort(volatile uint8_t &port, volatile uint8_t &direction, uint8_t mask);
    void output() const;
    void input() const;
    void set() const;
    void clear() const;
    void invert() const;

private:
    volatile uint8_t &port_;
    volatile uint8_t &direction_;
    uint8_t mask_;
};

#endif //MyPort