#ifndef E3_SIGNAL_H
#define E3_SIGNAL_H

#include "main.h"

class Signal
{
private:
    uint8_t errorPin, successPin;

    static const int delay_time = 100;

public:
    Signal(uint8_t errorPin, uint8_t successPin);

    void error();

    void success();
};

#endif