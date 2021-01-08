#if CALIBRATE

#include "calibrate.h"
#include "lcd.h"
#include "HX711.h"
#include "debug.h"
#include "buttons.h"

#define CHARMAP_SIZE 9
const struct
{
    char from[CHARMAP_SIZE];
    char to[CHARMAP_SIZE];
    float val[CHARMAP_SIZE];
} charMap = {
    .from = {'q', 'w', 'e', 'r', 'a', 's', 'd', 'f', 't'},
    .to = {'1', '2', '3', 'A', '4', '5', '6', 'B', TARE},
    .val = {0.1, 1, 10, 100, -0.1, -1, -10, -100, NAN}};

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

    String factorStr = String(calibration_factor);
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
    Serial.println("For Computer Serial interation use the following:");
    Serial.println("\tq, w, e, r --> calibration factor += 0.1, 1, 10, 100");
    Serial.println("\ta, s, d, f --> calibration factor -= 0.1, 1, 10, 100");
    Serial.println("For Keypad Matrix interaction use the following:");
    Serial.println("\t1, 2, 3, A --> calibration factor += 0.1, 1, 10, 100");
    Serial.println("\t4, 5, 6, B --> calibration factor -= 0.1, 1, 10, 100");
    Serial.println("Press t on computer or D button on keypad to tare scale\n\n");
}

void calibrate_scale()
{
    Serial.print("Reading: ");
    getWeight();

    Serial.print(weightString);
    Serial.print(" grams");
    Serial.print(" calibration_factor: ");
    Serial.print(calibration_factor);
    Serial.println();

    update_lcd();

    // using keypad to update factor
    getKeyPressed();

    // using serial to update factor
    if (Serial.available())
    {
        c = Serial.read(); // override keypad with serial input

        for (int i = 0; i < CHARMAP_SIZE; i++)
        {
            if (c == charMap.from[i])
            {
                c = charMap.to[i];
                break;
            }
        }
    }

    for (int i = 0; i < CHARMAP_SIZE; i++)
    {
        if (c == TARE)
        {
            tareScale();
            break;
        }
        else if (c == charMap.to[i])
        {
            calibration_factor += charMap.val[i];
            break;
        }
    }
}

#endif