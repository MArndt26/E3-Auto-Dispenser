#include "e3_digital.h"

E3_Digital::E3_Digital(uint8_t pump, uint8_t io1, uint8_t fs)
{
    PUMP_CTRL_PIN = pump;
    IO_1_PIN = io1;
    FOOT_SWITCH_PIN = fs;

    pinMode(PUMP_CTRL_PIN, OUTPUT);
    pinMode(IO_1_PIN, OUTPUT);
    pinMode(FOOT_SWITCH_PIN, INPUT);
    relaysOff();
}

void E3_Digital::relaysOn()
{
    digitalWrite(PUMP_CTRL_PIN, LOW); //turn on pump relay (active low)
    digitalWrite(IO_1_PIN, HIGH);     //turn on IO:1 relay
}

void E3_Digital::relaysOff()
{
    digitalWrite(PUMP_CTRL_PIN, HIGH); // turn off pump relay (active low)
    digitalWrite(IO_1_PIN, LOW);       // turn off IO:1 relay
}

int E3_Digital::checkFS()
{
    int val = digitalRead(FOOT_SWITCH_PIN);

    while (digitalRead(FOOT_SWITCH_PIN))
        ; // wait for switch to go low

    return val;
}

