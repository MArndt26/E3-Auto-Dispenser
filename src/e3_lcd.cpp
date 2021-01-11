#include "e3_lcd.h"

#ifndef VIRTUAL_SCREEN
E3_LCD::E3_LCD(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) : LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows)
{
}

void E3_LCD::start()
{
    LiquidCrystal_I2C::init();
    LiquidCrystal_I2C::backlight();
    LiquidCrystal_I2C::createChar(LOCKED, lockedDATA);     //create lock symbol
    LiquidCrystal_I2C::createChar(UNLOCKED, unlockedDATA); //creat unlock symbol
    LiquidCrystal_I2C::home();
    LiquidCrystal_I2C::print("LCD Initialized");
    LiquidCrystal_I2C::setCursor(0, 1);
    LiquidCrystal_I2C::print("Connect Scale");
}

#endif