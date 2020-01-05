#include <MyTimer.hpp>
#include <avr/io.h>
#include <avr/interrupt.h>

void start()
{
    TCNT1H = 0xFB;         //napełnienie licznika zegara
    TCNT1L = 0x1E;         //napełnienie licznika zegara
    TCCR1A = 0x00;         //zerowanie rejestru TCCR1A
    TCCR1B = (1 << CS12);  //Ustawienie prescalera na 256
    TIMSK1 = (1 << TOIE1); //Ustawienie timera w tryb przerwań od overflow
}

void stop()
{
    TIMSK1 = 0x00;
}

ISR(TIMER1_OVF_vect)
{
    TCNT1H = 0xFB;            //rejesr przepełnienia zegara - wysoki
    TCNT1L = 0x1E;            //rejestr przepełnienia zegara - niski
    _20_MS_COUNTER++;         //inkrementuje licznik 20 ms co 20 ms
    _20_MS_FLAG = TRUE;       //wystawienie flagi 20 ms
    if (_20_MS_COUNTER == 50) //po odliczeniu 1 s (50 x 20 ms)
    {
        _20_MS_COUNTER = 0;    //zerowanie licznika 20 ms
        _SEC_COUNTER++;        //inkrementacja licznika sekund
        _MASTER_SEC_COUNTER++; //inkrementacja licznika sekund
        _1_SEC_FLAG = TRUE;    //wystawienie flagi 1 s
    }
}