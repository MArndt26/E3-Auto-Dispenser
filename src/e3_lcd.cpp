#include "e3_lcd.h"

#ifndef SERIAL_DEBUG
E3_LCD::E3_LCD(uint8_t lcd_Addr, uint8_t lcd_cols, uint8_t lcd_rows) : LiquidCrystal_I2C(lcd_Addr, lcd_cols, lcd_rows)
{
}

// void E3_LCD::createCustomChars()
// {
//     LiquidCrystal_I2C::createChar(LOCKED, lockedDATA);     //create lock symbol
//     LiquidCrystal_I2C::createChar(UNLOCKED, unlockedDATA); //creat unlock symbol
// }

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

/**MAIN LCD object:
 *  params for constructor are as follows:
 *      (I2C address, disp resolution x, disp resolution y)
 */
// LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

/******************LDC SCREENS******************
 * HOME_PAGE:
 * ------------------
 * |WEIGHT:12345678g|
 * |SET VAL:1234567g|
 * ------------------
 *
 * PRESET_PAGE: NOTE: get to this page by pressing A, B, C, D
 *              once from home page
 * ------------------
 * |PREST:A 1234567g|
 * | PRESS # to SET |
 * ------------------
 *
 * PROGRAM_PAGE: NOTE: get to this page by pressing A, B, C, D
 *               twice from home page, once from PRESET_PAGE
 * ------------------
 * |PROGR:A 1234567g|
 * |PRESS # to PROGR|
 * ------------------
 *
 *
 * NOTE: the following button presses are INVALID input:
 *      AB    ::cannot switch from A PRESET to B PROGRAM_PAGE
 *      .       ::cannot start setting value with disp
 *      1..     ::cannot use back-to-back disp
 *      #       ::cannot enter/set an empty string
 *
 * NOTE: the following buttom presses are VALID input:
 *      A#      ::sets SET VAL to the A PRESET
 *      AA1234# ::sets A PRESET and SET VAL to 1234
 */
// void lcdInit()
// {
//     lcd.init();
//     lcd.backlight();
//     lcd.createChar(LOCKED, lockedDATA);     //create lock symbol
//     lcd.createChar(UNLOCKED, unlockedDATA); //creat unlock symbol
//     lcd.home();
//     lcd.print("LCD Initialized");
//     lcd.setCursor(0, 1);
//     lcd.print("Connect Scale");
// }

// /*
//  * HOME_PAGE:
//  * ------------------
//  * |WEIGHT:12345678g|
//  * |0SetVal:1234567g|
//  * ------------------
//  */
// void homeScreen()
// {
//     //first line
//     lcd.print(WEIGHT_MSG);
//     lcd.print(weightString);
//     for (unsigned int i = 0; i < DISP_WEIGHT_STR_MAX_LEN - weightString.length(); i++)
//     {
//         lcd.print(' ');
//     }
//     lcd.print("g");

//     //second line
//     lcd.setCursor(0, 1);
//     if (curString == "")
//     {
//         lcd.write(LOCKED);
//     }
//     else
//     {
//         lcd.write(UNLOCKED);
//     }
//     lcd.print(SET_MSG);

//     int length = DISP_SET_STR_MAX_LEN;
//     if (curString.length() > 0)
//     {
//         lcd.print(curString);
//         length -= curString.length();
//     }
//     else
//     {
//         lcd.print(setString);
//         length -= setString.length();
//     }

//     for (int i = 0; i < length; i++)
//     {
//         lcd.print(' ');
//     }
//     lcd.print("g");
// }

// /*
//  * PRESET_PAGE: NOTE: get to this page by pressing A, B, C, D
//  *              once from home page
//  * ------------------
//  * |PREST:A 1234567g|
//  * | PRESS # to SET |
//  * ------------------
//  */
// void presetScreen()
// {
//     //first line
//     lcd.print(PRESET_MSG);
//     lcd.print(cur_FN_Button);
//     lcd.print(getFN_String());
//     for (unsigned int i = 0; i < PRESET_DISP_SET_STR_MAX_LEN - getFN_String().length(); i++)
//     {
//         lcd.print(' ');
//     }
//     lcd.print("g");

//     //second line
//     lcd.setCursor(0, 1);

//     lcd.print(PRESET_ENTER_MSG);
// }

// /*
//  * PROGRAM_PAGE: NOTE: get to this page by pressing A, B, C, D
//  *               twice from home page, once from PRESET_PAGE
//  * ------------------
//  * |PROGR:A 1234567g|
//  * |PRESS # to PROGR|
//  * ------------------
//  */
// void programScreen()
// {
//     //first line
//     lcd.print(PROGRAM_MSG);
//     lcd.print(cur_FN_Button);
//     lcd.print(curString);
//     for (unsigned int i = 0; i < PROGRAM_DISP_SET_STR_MAX_LEN - curString.length(); i++)
//     {
//         lcd.print(' ');
//     }
//     lcd.print("g");

//     //second line
//     lcd.setCursor(0, 1);

//     lcd.print(PROGRAM_ENTER_MSG);
// }

// /*
//  * RUN_PAGE: NOTE: get to this page by pressing # from Home Page when SET VAL has been entered
//  * ------------------
//  * |S:1234 C:12345.6|
//  * | Press to Halt  |
//  * ------------------
//  */
// void runScreen()
// {
//     //first line
//     lcd.print("S:");
//     lcd.print(setString);

//     lcd.setCursor(8, 0);
//     lcd.print("C:");
//     lcd.print(curString);

//     //second line
//     lcd.setCursor(0, 1);
//     lcd.print(" Press to Halt");
// }

// void tareScreen()
// {
//     //first line
//     lcd.setCursor(0, 0);
//     lcd.print(TARE_MSG);

//     //second line
//     lcd.setCursor(0, 1);
//     lcd.print(BLANK_LINE);
// }

// void updateScreenImmediate()
// {
// #if HUSH
//     Serial.println("screen updated");
// #endif
//     lcd.setCursor(0, 0);
//     switch (curState)
//     {
//     case HOME_STATE:
//         homeScreen();
//         break;
//     case PRESET_STATE:
//         lcd.clear();
//         presetScreen();
//         break;
//     case PROGRAM_STATE:
//         lcd.clear();
//         programScreen();
//         break;
//     case RUN_STATE:
//         lcd.clear();
//         runScreen();
//         break;
//     }
// }

// void appendChar()
// {
//     if (curString.length() >= DISP_SET_STR_MAX_LEN) //check if you are trying to type off the screen
//     {
//         curString = "";
//     }
//     else
//     {
//         curString += c;
//     }
//     updateScreenImmediate();
//     time_now = millis();
// }

#endif