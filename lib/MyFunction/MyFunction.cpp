/*
    MyFunction.cpp
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

#include <avr/io.h>
#include <MyFunction.hpp>

#include <MyPort.hpp>

/*
    Funkcja SOS
    FunSOS(port)
    Wykorzystuje klasę NewPort z biblioteki MyPort
*/
void FunSOS(NewPort port)
{
    extern uint8_t _SEC_COUNTER; //odwołanie do globalnej zmiennej w main.cpp
    static uint8_t C2_C = 0;     //zmienna pomocnicza określająca stopień wykonania funkcji
    if (_SEC_COUNTER < 6)
    {
        C2_C = 0; //początkowe trzy mignięcia 1-6 sekund
    }
    else if (_SEC_COUNTER < 18)
    {
        C2_C = 1; //trzy długie mignięcia 6-18 sekund
    }
    else
    {
        C2_C = 2; //końcowe trzy mignięcia 18-24 sekund
    }
    //Switch wykonuje odpowiednią instrukcję w zależności od stopnia
    //w którym znajduje się aktualnie sygnał SOS
    switch (C2_C)
    {
    case 0:
        port.invert(); //zmiana stanu diód co sekundę
        break;
    case 1:
        if (((_SEC_COUNTER - 6) % 4) == 3)
        {
            port.invert(); //po trzech sekundach następuje zgaszene diody
        }
        if (((_SEC_COUNTER - 6) % 4) == 0)
        {
            port.invert(); //po czterech sekundach ponowne zapalenie
        }
        break;
    case 2:
        port.invert(); //zmiana stanu diód co sekundę
        if (_SEC_COUNTER == 24)
        {
            _SEC_COUNTER = 0; //zerowanie lokalnego licznika funkcji SOS
        }
        break;
    }
}