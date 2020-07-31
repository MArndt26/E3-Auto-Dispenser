/*--------------LDC VARS----------------*/
//Resource: https://gitlab.com/tandembyte/LCD_I2C

const byte WEIGHT_LINE_NUMBER = 0;
const byte SET_LINE_NUMBER = 1;

const byte SET_CURSOR_START = 4;
const byte MASS_CURSOR_START = 5;

const String SET_MSG = "SET VAl:";
const String WEIGHT_MSG = "WEIGHT:";

const byte DISP_SET_STR_MAX_LEN = 7;    //16 - 1 - 4; //Note: changing this can corrupt the data stored on eeprom
const byte DISP_WEIGHT_STR_MAX_LEN = 8; //16 - 1 - 5

String curString = "";

/**MAIN LCD object:
 *  params for constructor are as follows:
 *      (I2C address, disp resolution x, disp resolution y)
 */
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

/*-----------LCD FUNCTIONS---------------*/
void lcdInit()
{
    lcd.init();
    lcd.backlight();

    Serial.println("LCD Initialized");
}

void homeScreen()
{
    Serial.println("HOME SCREEN");
}

void presetScreen()
{
    Serial.print("PRESET SCREEN: ");
    Serial.println(cur_FN_Button);
}

void programScreen()
{
    Serial.print("PROGRAM SCREEN: ");
    Serial.println(cur_FN_Button);
}

void runScreen()
{
    Serial.println("RUN SCREEN");
}

void updateScreen()
{
    switch (curState)
    {
    case HOME_STATE:
        homeScreen();
        break;
    case PRESET_STATE:
        presetScreen();
        break;
    case PROGRAM_STATE:
        programScreen();
        break;
    case RUN_STATE:
        runScreen();
        break;
    }
}

void appendChar()
{
    lcd.setCursor(SET_MSG.length() + curString.length(), SET_LINE_NUMBER);
    curString += c;
    lcd.print(c);
}

// void clearDisplay()
// {
//     curString = "";

//     lcd.setCursor(SET_CURSOR_START, SET_LINE_NUMBER);
//     lcd.print(setString);

//     lcd.setCursor(MASS_CURSOR_START, WEIGHT_LINE_NUMBER);
//     lcd.print(curString);
// }

// void saveScreen()
// {
//     setString = curString;

//     clearDisplay();
// }

// void printHomePage()
// {
//     lcd.setCursor(0, WEIGHT_LINE_NUMBER);
//     lcd.print(WEIGHT_MSG);
//     lcd.print(curString);
//     lcd.setCursor(DISP_WEIGHT_STR_MAX_LEN, WEIGHT_LINE_NUMBER);
//     lcd.print('g');

//     lcd.setCursor(0, SET_LINE_NUMBER);
//     lcd.print(SET_MSG);
//     lcd.print(setString);
//     lcd.setCursor(DISP_SET_STR_MAX_LEN, SET_LINE_NUMBER);
//     lcd.print('g');
// }

/*
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
 * RUN_PAGE: NOTE: get to this page by pressing # from Home Page when SET VAL has been entered
 * ------------------
 * |WEIGHT:      50g|
 * |SET:50g PRESS ANY KEY TO STOP| --> scrolling text
 * ------------------
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