#ifndef CALIBRATE_H
#define CALIBRATE_H

#include "calibrate.h"
#include "lcd.h"
#include "HX711.h"
#include "scale.h"
#include "debug.h"
#include "buttons.h"

float factor = 464.5f; //464.5 worked best from initial testing

void update_lcd()
{
    //first line
    lcd.setCursor(0, 0);
    lcd.print("Grams: ");
    lcd.print(weightString);
    for (unsigned int i = 0; i < 8 - weightString.length(); i++)
    {
        lcd.print(' ');
    }
    lcd.print("g");

    //second line
    lcd.setCursor(0, 1);

    lcd.print("Calbr: ");

    int length = 8;

    String factorStr = String(factor);
    if (factorStr.length() > 0)
    {
        lcd.print(factorStr);
        length -= factorStr.length();
    }
    else
    {
        lcd.print(factorStr);
        length -= factorStr.length();
    }

    for (int i = 0; i < length; i++)
    {
        lcd.print(' ');
    }
    lcd.print("g");
}

void setup_calibrate_scale()
{
    debugInit();
    lcdInit();
    scaleInit();

    lcd.setCursor(0, 0);
    lcd.print("Calibration");
    Serial.println("HX711 calibration");
    Serial.println("Remove all weight from scale");
    Serial.println("After readings begin, place known weight on scale");
    Serial.println("Press + or a to increase calibration factor");
    Serial.println("Press - or z to decrease calibration factor");
    Serial.println("Press t to tare scale");
}

void calibrate_scale()
{
    scale.set_scale(factor); //Adjust to this calibration factor

    Serial.print("Reading: ");
    getWeight();

    Serial.print(weightString);
    Serial.print(" grams");
    Serial.print(" calibration_factor: ");
    Serial.print(factor);
    Serial.println();

    update_lcd();

    // using keypad to update factor
    getKeyPressed();

    // using serial to update factor
    if (Serial.available())
    {
        c = Serial.read(); // override keypad with serial input

        if (c == 't' || c == 'T')
        {
            c = TARE;
        }
    }

    if (c == '1')
    {
        factor += 0.1;
    }
    else if (c == '2')
    {
        factor -= 1;
    }
    else if (c == '3')
    {
        factor += 10;
    }
    else if (c == FN1_Button)
    {
        factor += 100;
    }
    else if (c == '4')
    {
        factor -= 0.1;
    }
    else if (c == '5')
    {
        factor -= 1;
    }
    else if (c == '6')
    {
        factor -= 10;
    }
    else if (c == FN2_Button)
    {
        factor -= 100;
    }
    else if (c == TARE)
    {
        tareScale();
    }
}

#endif //CALIBRATE_H