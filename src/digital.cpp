#include "digital.h"

void relaysOn()
{
    digitalWrite(PUMP_CTRL_PIN, LOW); //turn on pump relay (active low)
    digitalWrite(IO_1_PIN, HIGH);     //turn on IO:1 relay
}

void relaysOff()
{
    digitalWrite(PUMP_CTRL_PIN, HIGH); // turn off pump relay (active low)
    digitalWrite(IO_1_PIN, LOW);       // turn off IO:1 relay
}

int readFootSwitch()
{
#if NO_FOOTSWITCH
    return 0;
#else
    int val = digitalRead(FOOT_SWITCH_PIN);

    while (digitalRead(FOOT_SWITCH_PIN))
        ; // wait for switch to go low

    return val;
#endif
}

void relayInit()
{
    pinMode(PUMP_CTRL_PIN, OUTPUT);
    pinMode(IO_1_PIN, OUTPUT);
    pinMode(FOOT_SWITCH_PIN, INPUT);
    relaysOff();

#if HUSH
    Serial.println("Relays Initialized");
#endif
}
