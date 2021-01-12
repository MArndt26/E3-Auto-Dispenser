#ifndef DIGITAL_H
#define DIGITAL_H

#include "main.h"

class E3_Digital
{
private:
    uint8_t PUMP_CTRL_PIN = A3;
    uint8_t IO_1_PIN = A2;
    uint8_t FOOT_SWITCH_PIN = A1;

public:
    E3_Digital(uint8_t pump, uint8_t io1, uint8_t fs);

    void relaysOn();

    void relaysOff();

    int checkFS();
};

#endif