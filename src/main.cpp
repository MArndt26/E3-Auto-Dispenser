#include "main.h"
#include "e3_core.h"
#include "run.h"

void setup()
{
#ifdef SERIAL_DEBUG
  Serial.begin(9600);
  while (!Serial)
    ;
#endif
}

void loop()
{
  // Serial.print("\033[1;0H");
  // Serial.print("1234");
  // Serial.print("\033[2;0H");
  // Serial.print("4567");
  // delay(200);
  // screen.setCursor(0, 0);
  // screen.print("1234");
  // screen.setCursor(0, 1);
  // screen.print("4567");
  // delay(1000);
  // screen.clear();
  // delay(1000);
  run();
  // switch (curScreen)
  // {
  // case HOME:
  //   home();
  //   break;
  // case PRESET:
  //   // relaysOff();
  //   break;
  // case PROGRAM:
  //   // relaysOff();
  //   break;
  // case RUN:
  //   run();
  //   curScreen = HOME;
  //   break;
  // }
}