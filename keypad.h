

// /*--------------KEYPAD VARS------------------*/
char c; //holds value read in by keypad

const char FN1 = 'A';
const char FN2 = 'B';
const char FN3 = 'C';
const char TARE = 'D';
const char ENTER = '#';

char cur_FN_Button = '\0';

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

// //main keypad object
Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void getKeyPressed()
{
    c = keypad.getKey(); //returns the key that is pressed or ##### if no key is pressed
}

void keypadInit()
{
    //Keypad object has no () constructor
    Serial.println("Keypad Initialized");
}