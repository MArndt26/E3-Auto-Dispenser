#include "main.h"
#include "e3_core.h"
#include "run.h"
#include "home.h"
#include "preset.h"
#include "program.h"

void setup()
{
  // #ifdef SERIAL_DEBUG
  Serial.begin(9600);
  while (!Serial)
    ;
    // #endif

#ifndef SERIAL_DEBUG
  screen.start();
#endif

  e3_scale.setSetVal(memory.getFN1());

  keypad.setDebounceTime(50);
}

void loop()
{
  switch (curScreen)
  {
  case HOME:
    home();
    break;
  case PRESET:
    preset();
    break;
  case PROGRAM:
    program();
    break;
  case RUN:
    run();
    curScreen = HOME;
    break;
  }
}