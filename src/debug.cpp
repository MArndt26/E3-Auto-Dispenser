#include "debug.h"

/*---------------DEBUG FUNCTIONS------------*/
void debugInit()
{
    Serial.begin(9600); //for debuggin purposes
    while (!Serial)
    { // wait for serial port to connect. Needed for native USB
    }
    pinMode(errorPin, OUTPUT);  //set error pin as an output
    pinMode(successPin, OUTPUT); //set success pin as output

    #if HUSH
    Serial.println("User Functions Initialized");
    #endif
}

void userError()
{
    // flash error led
    digitalWrite(errorPin, HIGH);
    delay(100);
    digitalWrite(errorPin, LOW);
}

void userSuccess()
{
    // flash success led
    digitalWrite(successPin, HIGH);
    delay(100);
    digitalWrite(successPin, LOW);
}
#if HUSH
void debugVars()
{
    //print variabled to serial monitor
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
    Serial.print(weightString);
    Serial.println();
}
#endif
