#include "e3_signal.h"

Signal::Signal(uint8_t e, uint8_t s)
{
    errorPin = e;
    successPin = s;
}

void Signal::error()
{
    digitalWrite(errorPin, HIGH);
    delay(delay_time);
    digitalWrite(errorPin, LOW);
}

void Signal::success()
{
    digitalWrite(successPin, HIGH);
    delay(delay_time);
    digitalWrite(successPin, LOW);
}