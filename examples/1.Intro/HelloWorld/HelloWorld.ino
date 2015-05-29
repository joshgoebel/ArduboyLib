#include <SPI.h>
#include "Arduboy.h"
#include <EEPROM.h>

Arduboy arduboy;

void setup()
{
  // initialize the Arduboy hardware
  arduboy.start();
}

void loop()
{
    // no need to paint the screen more than our desired frame rate
    // and this helps the CPU sleep inbetween painting so you can get
    // longer battery life
    if (!arduboy.nextFrame())
        return;

    // put hello world in the middle of the scren
    arduboy.setCursor(0,25);
    arduboy.print("Hello World!");
}
