/*---------------DEBUG VARS-----------------*/
const byte errorPin = A1;
const byte successPin = A2;

/*---------------DEBUG FUNCTIONS------------*/
void debugInit()
{
    Serial.begin(9600); //for debuggin purposes
    while (!Serial)
    { // wait for serial port to connect. Needed for native USB
    }
    pinMode(errorPin, OUTPUT);
    pinMode(successPin, OUTPUT);

#if HUSH
    Serial.println("User Functions Initialized");
#endif
}

void userError(String msg)
{
#if HUSH
    Serial.print("Error: ");
    Serial.println(msg);
#endif
    digitalWrite(errorPin, HIGH);
    delay(100);
    digitalWrite(errorPin, LOW);
}

void userSuccess(String msg)
{
#if HUSH
    Serial.print("Success: ");
    Serial.println(msg);

#endif
    digitalWrite(successPin, HIGH);
    delay(100);
    digitalWrite(successPin, LOW);
}

void debugVars()
{
#if HUSH
    Serial.print("curStr: ");
    Serial.print(curString);
    Serial.print(", setStr: ");
    Serial.print(setString);
    Serial.print(", c: ");
    Serial.print(c);
    Serial.print(", cur_fn: ");
    Serial.print(cur_FN_Button);
    Serial.print(", fn1: ");
    Serial.print(fn1String);
    Serial.print(", fn2: ");
    Serial.print(fn2String);
    Serial.print(", fn3: ");
    Serial.print(fn3String);
    Serial.print(", weightString: ");
    Serial.println(weightString);
    Serial.println();
#endif
}
