#ifndef E3_LCD_H
#define E3_LCD_H

#include "main.h"

#ifndef SERIAL_DEBUG
#include <LiquidCrystal_I2C.h>
#include <avr/pgmspace.h>

class E3_LCD : public LiquidCrystal_I2C
{
private:
    uint8_t lockedDATA[8] = {B01110, B10001, B10001, B11111, B11011, B11011, B11111, B00000};

    uint8_t unlockedDATA[8] = {B01110, B10000, B10000, B11111, B11011, B11011, B11111, B00000};

public:
    static const byte LOCKED = 0;
    static const byte UNLOCKED = 1;
    E3_LCD(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);

    // void createCustomChars();

    void start();
};
#endif

#endif