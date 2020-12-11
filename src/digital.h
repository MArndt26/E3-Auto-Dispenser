/*---------------DIGITAL Vars-------------------*/
const byte PUMP_CTRL_PIN = A3;
const byte IO_1_PIN = A2;
const byte FOOT_SWITCH_PIN = A1;

void relaysOn()
{
    digitalWrite(PUMP_CTRL_PIN, HIGH);  //turn on pump relay
    digitalWrite(IO_1_PIN, HIGH);       //turn on IO:1 relay
}

void relaysOff()
{
    digitalWrite(PUMP_CTRL_PIN, LOW);  // turn off pump relay
    digitalWrite(IO_1_PIN, LOW);       // turn off IO:1 relay
}

int readFootSwitch()
{
    int val = digitalRead(FOOT_SWITCH_PIN);

    while (digitalRead(FOOT_SWITCH_PIN)); // wait for switch to go low

    return val;
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
