/*-----------STATE VARS-------------*/
const byte PROGRAM_STATE = 0;
const byte RUN_STATE = 1;

byte curState = 0;

/*-------------EEPROM VALS------------*/
//https://www.arduino.cc/en/Reference/EEPROMGet

//change this to use the integer return value form eeprom_readAnything()
int eeAddress = 0;
// int FN_A_Addr = sizeof(String);
// int FN_B_Addr = sizeof(String) * 2;
// int FN_C_Addr = sizeof(String) * 3;
// int FN_D_Addr = sizeof(String) * 4;

/*--------------LDC VARS----------------*/
/** Resource: https://gitlab.com/tandembyte/LCD_I2C
 * 
 * params for constructor are as follows:
 * (I2C address, disp resolution x, disp resolution y)
 * 
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
 * PROGRAM_PAGE: NOTE: get to this pabe by pressing A, B, C, D
 *               twice from home page, once from PRESET_PAGE
 * ------------------
 * |PROGR:A 1234567g|
 * |PRESS # to PROGR|
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

const byte WEIGHT_LINE_NUMBER = 0;
const byte SET_LINE_NUMBER = 1;

const byte SET_CURSOR_START = 4;
const byte MASS_CURSOR_START = 5;

const String SET_MSG = "SET VAl:";
const String WEIGHT_MSG = "WEIGHT:";

const byte DISP_SET_STR_MAX_LEN = 7;    //16 - 1 - 4; //Note: changing this can corrupt the data stored on eeprom
const byte DISP_WEIGHT_STR_MAX_LEN = 8; //16 - 1 - 5

String curString = "";
String setString = "";

char c; //character to read in from user

//main LCD object
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 2);

/*--------------KEYPAD VARS------------------*/
const char CLEAR = 'C';
const char START_STOP = 'D';

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

//main keypad object
Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

/*----------------SCALE VARS----------------*/
const int LOADCELL_DOUT_PIN = 10;
const int LOADCELL_SCK_PIN = 11;

String massString = "";

HX711 scale;

/*---------------Relay Vars-------------------*/
const byte PUMP_CTRL_PIN = 13;
const byte IO_1_PIN = 11;

/*---------------ERROR VARS-----------------*/
const byte errorPin = A1;
const byte successPin = A2;
