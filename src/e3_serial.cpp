#include "e3_serial.h"

//percision is 1 followed by the number of digits of percision desired
#define PERCISION 10

void floatToString(double input, int *whole, unsigned int *frac)
{
    *whole = (int)input;
    if (input >= 0)
    {
        *frac = (input - int(input)) * PERCISION;
    }
    else
    {
        *frac = (int(input) - input) * PERCISION;
    }
}

#define CURSOR_X_POS 4
#define CURSOR_Y_POS 2

E3_Serial::E3_Serial()
{
    clear(); //clean up terminal before emulating lcd

    Serial.print("LCD Initialized");

    setCursor(1, 0);

    Serial.print("Connect Scale");
}

void E3_Serial::clear()
{
    Serial.print(CLEAR);
}

void E3_Serial::setCursor(int x, int y)
{
    //Serial terminal is 1 indexed
    y++;
    x++;
    char y_c = '0' + y;
    char x_c = '0' + x;

    CURSOR_POS[CURSOR_Y_POS] = y_c;
    CURSOR_POS[CURSOR_X_POS] = x_c;

    Serial.print(CURSOR_POS);
}

void E3_Serial::home()
{
    Serial.print(HOME);
}

void E3_Serial::print(const char *str)
{
    Serial.print(str);
}

void E3_Serial::write(uint8_t num)
{
    Serial.print(num);
}
