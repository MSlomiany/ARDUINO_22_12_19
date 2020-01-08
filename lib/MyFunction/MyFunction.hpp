/*
    MyFunction.hpp
    Testowa biblioteka do obsługi funkcji
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

//Definicja pliku nagłówkowego
#ifndef MyFunction_hpp
#define MyFunction_hpp
//Biblioteki systemowe
#include <avr/io.h>
//Biblioteki lokalne
#include <MyPort.hpp>

void FunSOS(NewPort port);
void FunPWM(NewPort port, volatile uint8_t &dutyCycle1, volatile uint8_t &dutyCycle2);
void FunChain(NewPort port, uint8_t vector[]);

#endif