/*--------------LDC VARS----------------*/
//Resource: https://gitlab.com/tandembyte/LCD_I2C

//HOME SCREEN
const byte WEIGHT_LINE_NUMBER = 0;
const byte SET_LINE_NUMBER = 1;

const byte SET_CURSOR_START = 4;
const byte MASS_CURSOR_START = 5;

const String SET_MSG = "SET VAl:";
const String WEIGHT_MSG = "WEIGHT:";

const byte DISP_SET_STR_MAX_LEN = 7;    //16 - 1 - 4; //Note: changing this can corrupt the data stored on eeprom
const byte DISP_WEIGHT_STR_MAX_LEN = 8; //16 - 1 - 5

//PRESET SCREEN
const String PRESET_MSG = "PREST:";
const String PRESET_ENTER_MSG = " PRESS # to SET ";

const byte PRESET_DISP_SET_STR_MAX_LEN = 9;

//PROGRAM SCREEN
const String PROGRAM_MSG = "PROGR:";
const String PROGRAM_ENTER_MSG = "PRESS # to PROGR";

const byte PROGRAM_DISP_SET_STR_MAX_LEN = 9;

//RUN SCREEN
const String RUN_WARN_MSG = "g [PRESS ANY KEY TO STOP]";

String curString = ""; //value user is currently typing in
String setString = ""; //set value saved to eeprom

String fn1String = ""; //fn1 value saved to eeprom
String fn2String = ""; //fn2 value saved to eeprom
String fn3String = ""; //fn3 value saved to eeprom

/**MAIN LCD object:
 *  params for constructor are as follows:
 *      (I2C address, disp resolution x, disp resolution y)
 */
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

/*--------------LCD FUNCTIONS-----------------*/
String getFN_String()
{
    if (cur_FN_Button == FN1_Button)
    {
        return fn1String;
    }
    else if (cur_FN_Button == FN2_Button)
    {
        return fn2String;
    }
    else if (cur_FN_Button == FN3_Button)
    {
        return fn3String;
    }
    return "NULL";
}

/*--------------SERIAL SCREEN DEBUGGING--------*/
void serialSetCursor(int row, int col)
{
    char r = '0' + row;
    char c = '0' + col;
    String str = "\033[";
    str += r;
    str += ';';
    str += c;
    str += 'H';

    Serial.print(str);
}

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
void lcdInit()
{
    lcd.init();
    lcd.backlight();
#if HUSH
    Serial.println("LCD Initialized");
#endif
}

/*
 * HOME_PAGE:
 * ------------------
 * |WEIGHT:12345678g|
 * |SET VAL:1234567g|
 * ------------------
 */
void homeScreen()
{
    //first line
    Serial.print(WEIGHT_MSG);
    Serial.print(weightString);
    for (int i = 0; i < DISP_WEIGHT_STR_MAX_LEN - weightString.length(); i++)
    {
        Serial.print(' ');
    }
    Serial.println("g");

    //second line
    Serial.print(SET_MSG);

    int length = DISP_SET_STR_MAX_LEN;
    if (curString.length() > 0)
    {
        Serial.print(curString);
        length -= curString.length();
    }
    else
    {
        Serial.print(setString);
        length -= setString.length();
    }

    for (int i = 0; i < length; i++)
    {
        Serial.print(' ');
    }
    Serial.println("g");
}
/*
 * PRESET_PAGE: NOTE: get to this page by pressing A, B, C, D
 *              once from home page
 * ------------------
 * |PREST:A 1234567g|
 * | PRESS # to SET |
 * ------------------
 */
void presetScreen()
{
    //first line
    Serial.print(PRESET_MSG);
    Serial.print(getFN_String());
    for (int i = 0; i < PRESET_DISP_SET_STR_MAX_LEN - getFN_String().length(); i++)
    {
        Serial.print(' ');
    }
    Serial.println("g");

    //second line
    Serial.print(PRESET_ENTER_MSG);
}

/*
 * PROGRAM_PAGE: NOTE: get to this page by pressing A, B, C, D
 *               twice from home page, once from PRESET_PAGE
 * ------------------
 * |PROGR:A 1234567g|
 * |PRESS # to PROGR|
 * ------------------
 */
void programScreen()
{
    //first line
    Serial.print(PROGRAM_MSG);
    Serial.print(curString);
    for (int i = 0; i < PROGRAM_DISP_SET_STR_MAX_LEN - curString.length(); i++)
    {
        Serial.print(' ');
    }
    Serial.println("g");

    //second line
    Serial.print(PROGRAM_ENTER_MSG);
}

/*
 * RUN_PAGE: NOTE: get to this page by pressing # from Home Page when SET VAL has been entered
 * ------------------
 * |WEIGHT:      50g|
 * |SET:50g PRESS ANY KEY TO STOP| --> scrolling text
 * ------------------
 */
void runScreen()
{
    //first line
    Serial.print(WEIGHT_MSG);
    Serial.print(weightString);
    for (int i = 0; i < DISP_WEIGHT_STR_MAX_LEN - weightString.length(); i++)
    {
        Serial.print(' ');
    }
    Serial.println("g");

    //second line
    Serial.print(SET_MSG);
    Serial.print(setString);
    Serial.print(RUN_WARN_MSG);
}

void updateScreen()
{
    serialSetCursor(0, 0);
    switch (curState)
    {
    case HOME_STATE:
        Serial.println("HOME SCREEN");
        homeScreen();
        break;
    case PRESET_STATE:
        Serial.print("PRESET SCREEN: ");
        Serial.println(cur_FN_Button);
        presetScreen();
        break;
    case PROGRAM_STATE:
        Serial.print("PROGRAM SCREEN: ");
        Serial.println(cur_FN_Button);
        programScreen();
        break;
    case RUN_STATE:
        Serial.println("RUN SCREEN");
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