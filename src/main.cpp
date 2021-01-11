#include "main.h"
#include "e3_core.h"
#include "run.h"
#include "home.h"
#include "preset.h"

void setup()
{
  // #ifdef SERIAL_DEBUG
  Serial.begin(9600);
  while (!Serial)
    ;
  // #endif

  screen.init();
  screen.backlight();
  screen.createCustomChars();
  screen.home();
  screen.print("LCD Initialized");
  screen.setCursor(0, 1);
  screen.print("Connect Scale");

  signal.success();

  e3_scale.setSetVal(memory.getFN1());

  signal.success();
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
    // relaysOff();
    break;
  case RUN:
    run();
    curScreen = HOME;
    break;
  }
}