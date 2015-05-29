#include <SPI.h>
#include "Arduboy.h"
#include <EEPROM.h>

Arduboy arduboy;
Physics physics;

Rect sprite;
#define DOWN 1
#define UP -1
int direction;

void setup()
{
  // initialize the Arduboy hardware
  arduboy.start();
  // set a reasonable frame rate for our sketch
  arduboy.setFrameRate(60);

  sprite.x = 0;
  sprite.y = 0;
  sprite.height = 8;
  sprite.width = 128;

  direction = DOWN;
}

void loop()
{
    // no need to paint the screen more than our desired frame rate
    // and this helps the CPU sleep inbetween painting so you can get
    // longer battery life
    if (!arduboy.nextFrame())
        return;

    // draw hello world at our current Y position
    arduboy.setCursor(0, sprite.y);
    arduboy.print("Hello World!");

    // move hello world up or down (+1 or -1)
    sprite.y += direction;

    // if hello world hits the screen border then it bounces back
    if (physics.collide(sprite, TOP_EDGE) {
      direction=DOWN;
    } elsif (physics.collide(sprite, BOTTOM_EDGE)) {
      direction=UP;
    }

}
