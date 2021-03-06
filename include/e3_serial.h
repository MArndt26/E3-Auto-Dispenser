#ifndef E3_SERIAL_H
#define E3_SERIAL_H

#include "main.h"

#ifdef VIRTUAL_SCREEN

#define CLEAR_STR_LEN 7
#define CURSOR_POS_STR_LEN 8
#define HOME_STR_LEN 8

class E3_Serial
{
private:
    const char CLEAR[CLEAR_STR_LEN] = "\033[2J";
    char CURSOR_POS[CURSOR_POS_STR_LEN] = "\033[0;0H";
    const char HOME[HOME_STR_LEN] = "\033[0;0H";

public:
    byte LOCKED = 1;
    byte UNLOCKED = 0;

    E3_Serial();

    void clear();

    void home();

    void setCursor(int x, int y);

    void print(const char *str);

    void write(uint8_t num);
};

#endif

#endif