/*---------------DEBUG VARS-----------------*/
const byte errorPin = A1;
const byte successPin = A2;

/*---------------DEBUG FUNCTIONS------------*/
void debugInit()
{
    Serial.begin(9600); //for debuggin purposes
    pinMode(errorPin, OUTPUT);
    pinMode(successPin, OUTPUT);

    Serial.println("User Functions Initialized");
}

void userError()
{
    Serial.println("Error");
    digitalWrite(errorPin, HIGH);
    delay(100);
    digitalWrite(errorPin, LOW);
}

void userSuccess()
{
    Serial.println("Success");
    digitalWrite(successPin, HIGH);
    delay(100);
    digitalWrite(successPin, LOW);
}

void userError(String msg)
{
    Serial.print(msg);
    Serial.print(": ");
    userError();
}

void userSuccess(String msg)
{
    Serial.print(msg);
    Serial.print(": ");
    userSuccess();
}

void printLCD()
{
    Serial.println("------------------");
    //first line
    Serial.print("|");
    Serial.print(WEIGHT_MSG);
    // Serial.print(curString);
    for (int i = 0; i < DISP_WEIGHT_STR_MAX_LEN; i++)
    {
        Serial.print(' ');
    }
    Serial.println("g|");

    //second line
    Serial.print("|");
    Serial.print(SET_MSG);
    Serial.print(curString);
    for (int i = 0; i < DISP_SET_STR_MAX_LEN - curString.length(); i++)
    {
        Serial.print(' ');
    }
    Serial.println("g|");

    Serial.println("------------------");
}

void debugVars()
{
    Serial.print("curStr: ");
    Serial.print(curString);
    Serial.print(", setStr: ");
    Serial.print(setString);
    Serial.print(", c: ");
    Serial.print(c);
    Serial.print(", cur_fn: ");
    Serial.print(cur_FN_Button);
    Serial.print(", fn: {");
    for (int i = 0; i < 3; i++)
    {
        Serial.print(fnStrings[i]);
        Serial.print(", ");
    }

    Serial.print("}");
    Serial.println();
}
