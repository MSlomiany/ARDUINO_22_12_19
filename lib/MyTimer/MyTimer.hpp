#ifndef MyTimer_hpp
#define MyTimer_hpp

#include <avr/io.h>

class MyTimer
{
public:
    MyTimer(){};
    void start();
    void stop();
    void clearFlag();
    void getFlag();
};

#endif