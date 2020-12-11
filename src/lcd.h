/*--------------LDC VARS----------------*/
//Resource: https://gitlab.com/tandembyte/LCD_I2C

//Custom Characters
const byte LOCKED = 1;
byte lockedDATA[] ={
    B01110,
    B10001,
    B10001,
    B11111,
    B11011,
    B11011,
    B11111,
    B00000 };

const byte UNLOCKED = 0;
byte unlockedDATA[] ={
    B01110,
    B10000,
    B10000,
    B11111,
    B11011,
    B11011,
    B11111,
    B00000 };

//SCREEN
const byte SCREEN_X = 16;

//HOME SCREEN
const byte WEIGHT_LINE_NUMBER = 0;
const byte SET_LINE_NUMBER = 1;

const byte SET_CURSOR_START = 4;
const byte MASS_CURSOR_START = 5;

const String SET_MSG = "SetVal:";
const String WEIGHT_MSG = "WEIGHT:";

const byte DISP_SET_STR_MAX_LEN = 7;    //16 - 1 - 4; //Note: changing this can corrupt the data stored on eeprom
const byte DISP_WEIGHT_STR_MAX_LEN = 8; //16 - 1 - 5

//SHIFTING VARS
unsigned short offset = 0;

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

//TARE SCREEN
const String TARE_MSG = "------TARE------";
const String BLANK_LINE = "                ";

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
    lcd.createChar(LOCKED, lockedDATA);     //create lock symbol
    lcd.createChar(UNLOCKED, unlockedDATA); //creat unlock symbol
    lcd.setCursor(0, 0);
    #if HUSH
    Serial.println("LCD Initialized");
    #endif
}

/*
 * HOME_PAGE:
 * ------------------
 * |WEIGHT:12345678g|
 * |0SetVal:1234567g|
 * ------------------
 */
void homeScreen()
{
    //first line
    lcd.print(WEIGHT_MSG);
    lcd.print(weightString);
    for (unsigned int i = 0; i < DISP_WEIGHT_STR_MAX_LEN - weightString.length(); i++)
    {
        lcd.print(' ');
    }
    lcd.print("g");

    //second line
    lcd.setCursor(0, 1);
    if (curString == "")
    {
        lcd.write(LOCKED);
    }
    else
    {
        lcd.write(UNLOCKED);
    }
    lcd.print(SET_MSG);

    int length = DISP_SET_STR_MAX_LEN;
    if (curString.length() > 0)
    {
        lcd.print(curString);
        length -= curString.length();
    }
    else
    {
        lcd.print(setString);
        length -= setString.length();
    }

    for (int i = 0; i < length; i++)
    {
        lcd.print(' ');
    }
    lcd.print("g");
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
    lcd.print(PRESET_MSG);
    lcd.print(cur_FN_Button);
    lcd.print(getFN_String());
    for (unsigned int i = 0; i < PRESET_DISP_SET_STR_MAX_LEN - getFN_String().length(); i++)
    {
        lcd.print(' ');
    }
    lcd.print("g");

    //second line
    lcd.setCursor(0, 1);

    lcd.print(PRESET_ENTER_MSG);
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
    lcd.print(PROGRAM_MSG);
    lcd.print(cur_FN_Button);
    lcd.print(curString);
    for (unsigned int i = 0; i < PROGRAM_DISP_SET_STR_MAX_LEN - curString.length(); i++)
    {
        lcd.print(' ');
    }
    lcd.print("g");

    //second line
    lcd.setCursor(0, 1);

    lcd.print(PROGRAM_ENTER_MSG);
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
    lcd.print(WEIGHT_MSG);
    lcd.print(weightString);
    for (unsigned int i = 0; i < DISP_WEIGHT_STR_MAX_LEN - weightString.length(); i++)
    {
        lcd.print(' ');
    }
    lcd.print("g");

    //second line
    lcd.setCursor(0, 1);

    String msg = SET_MSG + setString + RUN_WARN_MSG;

    if (offset + SCREEN_X / 2 >= msg.length()) //check if end of message is in middle of screen
    {
        offset = 0; //go back to start
    }
    else if (offset + SCREEN_X < msg.length()) //substring will go out of bounds
    {
        msg = msg.substring(offset, msg.length());
    }
    else
    {
        msg = msg.substring(offset, offset + SCREEN_X);
        msg += "         ";
    }

    lcd.print(msg);
}

void tareScreen()
{
    //first line
    lcd.setCursor(0, 0);
    lcd.print(TARE_MSG);

    //second line
    lcd.setCursor(0, 1);
    lcd.print(BLANK_LINE);
}

void updateScreenImmediate()
{
    #if HUSH
    Serial.println("screen updated");
    #endif
    lcd.setCursor(0, 0);
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
    if (curString.length() >= DISP_SET_STR_MAX_LEN) //check if you are trying to type off the screen
    {
        curString = "";
    }
    else
    {
        curString += c;
    }
    updateScreenImmediate();
    time_now = millis();
}