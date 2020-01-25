
/*******************************************************************
 * 
 * \brief
 * Plik main.cpp zawiera listę załączonych bibliotek
 * oraz funkcję główną programu
 * 
 *******************************************************************/
///Github check 25_01
#define MY 7

/***********************BIBLIOTEKI*******************************/
#include <avr/io.h>        //mapa mikroprocesora
#include <avr/interrupt.h> //obsluga przerwań
//#include <avr/sleep.h>     //obsługa trybu uśpienia
#include <avr/wdt.h>
/**
 * \brief
 * Biblioteki lokalne
 * katalog lib/
 */
#include <MyPort.hpp>
#include <MyFunction.hpp>
/***********************DEFINICJE STAŁYCH************************/

#define TRUE 1
#define FALSE 0
//wypełnienie cyklu PWM 0-255
#define PWM_DUTY_CYCLE 0xFF

/***********************ZMIENNE GLOBALNE*************************/

volatile bool _20_MS_FLAG;    //flaga co 20 ms
volatile bool _1_SEC_FLAG;    //flaga co 1 s
uint8_t _20_MS_COUNTER;       //licznik 20 ms - inkrementacja co 1 ms (1-20)
uint8_t _SEC_COUNTER;         //licznik sekund - lokalny, resetowalny
uint64_t _MASTER_SEC_COUNTER; //licznik sekund

/***********************UŻYTE PINY*******************************/

uint8_t mask_led = ((1 << PD2) | (1 << PD3));
uint8_t mask_pwm = ((1 << PD5) | (1 << PD6));
uint8_t mask_debug = ((1 << PD4));
uint8_t mask_test = ((1 << PD7));

/***********************MASKA FUNKCJI CHAIN**********************/

uint8_t sos_chain[] = {1, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 2};

/***********************FUNKCJA PRZERWANIA - TIMER 1*************/

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

/***********************FUNKCJA GŁÓWNA***************************/
int main()
{
    //INICJALIZACJA PORTÓW
    NewPort Led(PORTD, DDRD, mask_led);
    NewPort Pwm(PORTD, DDRD, mask_pwm);
    NewPort Debug(PORTD, DDRD, mask_debug);
    NewPort Test(PORTD, DDRD, mask_test);
    Led.output();
    Pwm.output();
    Debug.output();
    Test.output();
    Led.set();
    Test.set();
    //ZEROWANIE LICZNIKÓW
    _20_MS_FLAG = FALSE;
    _1_SEC_FLAG = FALSE;
    _20_MS_COUNTER = 0;
    _SEC_COUNTER = 0;
    _MASTER_SEC_COUNTER = 0;

    //BLOK INICJALIZACJI PRZERWAŃ
    /*
        Ustawienie rejestrów zegara TIM1
        Zegar TIM1 jest 16-bitowy, ustawiony w tryb przepełnienia
        Aby dobrze ustawić rejestr zegara:
        Atmega328p jest taktowana zegarem 16 MHz
        Prescaler (w TCCR1B) ustawiamy w tryb skalowania przez 256
        16 000 000 / 256 = 62 500 ticków zegara na sekundę
        1s/20ms = 50
        62 500 / 50 = 1250 -> tyle ticków zegar daje przez 20 ms
        Rejestr zegara ma 16 bitów, 2^16 = 65 536
        Co oznacza że możemy zapełnić wartości od 0 do 65 535
        65 535 - 1250 = 64285
    */

    //TIMER 1
    TCNT1H = 0xFB;         //napełnienie licznika zegara
    TCNT1L = 0x1E;         //napełnienie licznika zegara
    TCCR1A = 0x00;         //zerowanie rejestru TCCR1A
    TCCR1B = (1 << CS12);  //Ustawienie prescalera na 256
    TIMSK1 = (1 << TOIE1); //Ustawienie timera w tryb przerwań od overflow

    //TIMER 0
    //COM0A/B1 - ustawienie pinów OC0A i OC0B (PD5 i PD6) w tryb PWM
    //WGM01/0 - ustawienie trybu pracy timera w Fast PWM
    TCCR0A |= ((1 << COM0A1) | (1 << COM0B1) | (1 << COM0B0) | (1 << WGM01) | (1 << WGM00));
    TCCR0B |= ((1 << CS01) | (1 << CS00));
    OCR0A = 0x00;
    OCR0B = 0x00;

    /***********************GLOBALNA AKTYWACJA PRZERWAŃ**************/
    sei(); //globalna aktywacja przerwan

    /***********************PĘTLA GŁÓWNA PROGRAMU********************/
    while (TRUE)
    {
        //MODUŁ STEROWANIA PWM
        if (_20_MS_FLAG == TRUE)
        {
            _20_MS_FLAG = FALSE;
            FunPWM(Debug, OCR0A, OCR0B);
        } //KONIEC MODUŁU PWM
        //MODUŁ SOS
        if (_1_SEC_FLAG == TRUE) //wywołanie co 1 sekundę
        {
            _1_SEC_FLAG = FALSE; //na samym początku zerowanie flagi
            FunSOS(Led);
            FunChain(Test, sos_chain);
        } //KONIEC MODUŁU SOS
    }
    return 0;
    //KONIEC FUNKCJI GŁÓWNEJ
}