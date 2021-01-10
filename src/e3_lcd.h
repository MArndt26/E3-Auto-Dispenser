#ifndef E3_LCD_H
#define E3_LCD_H

#include "main.h"
#include <LiquidCrystal_I2C.h>

class E3_LCD : public LiquidCrystal_I2C
{
private:
    uint8_t lockedDATA[8] = {B01110, B10001, B10001, B11111, B11011, B11011, B11111, B00000};

    uint8_t unlockedDATA[8] = {B01110, B10000, B10000, B11111, B11011, B11011, B11111, B00000};

public:
    byte LOCKED = 0;
    byte UNLOCKED = 1;
    E3_LCD(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows);
};

#endif