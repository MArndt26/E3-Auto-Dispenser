#include "main.h"
#include "e3_core.h"
#include "run.h"
#include "home.h"
#include "preset.h"
#include "program.h"
#include "calibrate.h"

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

#ifndef INITIALIZE_PERMANENT_MEM
  memory.fn1 = 100;
  memory.fn2 = 200;
  memory.fn3 = 300;
  memory.c_factor = 464.5f;
#endif

  e3_scale.setVal = memory.fn1;

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
  case CALIBRATE:
    calibrate();
    break;
  }
}