/*---------------DIGITAL Vars-------------------*/
const byte PUMP_CTRL_PIN = A3;
const byte IO_1_PIN = A2;
const byte FOOT_SWITCH_PIN = A1;

void relaysOn()
{
    digitalWrite(PUMP_CTRL_PIN, HIGH);
    digitalWrite(IO_1_PIN, HIGH);
}

void relaysOff()
{
    digitalWrite(PUMP_CTRL_PIN, LOW);
    digitalWrite(IO_1_PIN, LOW);
}

boolean readFootSwitch()
{
    return digitalRead(FOOT_SWITCH_PIN) == HIGH;
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
