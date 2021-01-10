#include "e3_signal.h"

Signal::Signal(uint8_t e, uint8_t s)
{
    errorPin = e;
    successPin = s;
}

void Signal::error()
{
#ifdef VIRTUAL_SIGNAL
    Serial.print("\033[s");     //save cursor position
    Serial.print("\033[1;25f"); //move cursor to line 1 col 25
    Serial.print("error");
    delay(delay_time);
    Serial.print("\b\b\b\b\b");
    Serial.print("\033[u"); //restore cursor position
#else
    digitalWrite(errorPin, HIGH);
    delay(delay_time);
    digitalWrite(errorPin, LOW);
#endif
}

void Signal::success()
{
#ifdef VIRTUAL_SIGNAL
    Serial.print("\033[s");     //save cursor position
    Serial.print("\033[2;25f"); //move cursor to line 2 col 25
    Serial.print("success");
    delay(delay_time);
    Serial.print("\b\b\b\b\b\b\b");
    Serial.print("\033[u"); //restore cursor position
#else
    digitalWrite(successPin, HIGH);
    delay(delay_time);
    digitalWrite(successPin, LOW);
#endif
}