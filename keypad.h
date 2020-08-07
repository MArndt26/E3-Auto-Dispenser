/*--------------KEYPAD VARS------------------*/
char c; //holds value read in by keypad

const char FN1_Button = 'A';
const char FN2_Button = 'B';
const char FN3_Button = 'C';
const char TARE = 'D';
const char ENTER = '#';

char prev_FN_Button = '\0';
char cur_FN_Button = '\0';

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] ={
    { '1', '2', '3', 'A' },
    { '4', '5', '6', 'B' },
    { '7', '8', '9', 'C' },
    { '*', '0', '#', 'D' } };

byte rowPins[ROWS] ={ 9, 8, 7, 6 };
byte colPins[COLS] ={ 5, 4, 3, 2 };

// //main keypad object
Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

/*---------------KEYPAD FUNCTIONS------------------*/

void keypadInit()
{
    //Keypad object has no () constructor
    #if HUSH
    Serial.println("Keypad Initialized");
    #endif
}

boolean getKeyPressed()
{
    c = keypad.getKey(); //returns the key that is pressed or /0 if no key is pressed

    #if NO_HOME_KEYPAD_ENTER
    if (curState == HOME_STATE && c == ENTER)
    {
        c = '\0';
        return false;
    }
    #endif

    #if SERIAL_DEBUG
    while (Serial.available() > 0)
    {
        c = Serial.read();

        #if HUSH
        if (c != '\0')
        {
            Serial.print("char: ");
            Serial.println(c);
        }
        #endif
    }
    #endif
    return true;
}

void clearFN_Buttons()
{
    prev_FN_Button = '\0';
    cur_FN_Button = '\0';
}