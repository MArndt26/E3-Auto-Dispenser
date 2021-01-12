#include "common.h"
#include "e3_core.h"

void tareScreen()
{
    screen.clear();
    //first line
    screen.home();
    screen.print("------TARE------");
}

void scaleDisconnectedScreen()
{
    screen.clear();
    //first line
    screen.home();
    screen.print("Reconnect Scale");
}