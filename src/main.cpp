#include "main.h"
#include "e3_core.h"
#include "run.h"
#include "home.h"

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
  home();
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