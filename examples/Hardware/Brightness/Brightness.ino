 /*
  Breakout
 Copyright (C) 2011 Sebastian Goscik
 All rights reserved.

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 */

#include <SPI.h>
#include "Arduboy.h"
#include <EEPROM.h>

Arduboy arduboy;

#include "pins_arduino.h" // Arduino pre-1.0 needs this


void setup()
{
  arduboy.start();
  arduboy.setFrameRate(30);
}



uint8_t brightness = 0x0;
uint8_t real_brightness = 0x0;
uint8_t precharge1 = 0x0f;
uint8_t precharge2 = 0x01;

void loop()
{
  // pause render until it's time for the next frame
  if (!(arduboy.nextFrame()))
    return;

  if (arduboy.justPressed(UP_BUTTON)) {
    if ((int)brightness+32 > 255) {
      brightness=255;
    }
    else {
      brightness+=10;
    }
  } else if (arduboy.justPressed(DOWN_BUTTON)) {
    if ((int)brightness-32<0) {
      brightness=0;
    } else {
    brightness-=10;
    }
  }

  real_brightness = brightness << 1 ;
  // kick on precharge 2 for brightness kick
  precharge2 = (brightness & 0b10000000) >> 7;
  precharge1 = (brightness >>4) | 0x02;


  // if (arduboy.justPressed(UP_BUTTON)) {
  //   if ((int)brightness+64 > 255) {
  //     brightness=0;
  //   }
  //   else {
  //     brightness+=63;
  //   }
  // } else if (arduboy.justPressed(DOWN_BUTTON)) {
  //   brightness-=63;
  // }

  // if (arduboy.justPressed(LEFT_BUTTON)) {
  //   precharge1 -= 1;
  //   precharge1 &= 0x0f;
  // } else if (arduboy.justPressed(RIGHT_BUTTON)) {
  //   precharge1 += 1;
  //   precharge1 &= 0x0f;
  // }

  // if (arduboy.justPressed(A_BUTTON)) {
  //   precharge2 -= 1;
  //   precharge2 &= 0x0f;
  // } else if (arduboy.justPressed(B_BUTTON)) {
  //   precharge2 += 1;
  //   precharge2 &= 0x0f;
  // }

  uint8_t precharge = (precharge1 << 4) + (precharge2 & 0x0f);

  arduboy.clearDisplay();
  arduboy.setCursor(0,0);
  arduboy.println("Set");
  arduboy.println(brightness);

  arduboy.println("Brightness");
  arduboy.println(real_brightness, 16);
  arduboy.println("Precharge");
  arduboy.println(precharge, 16);

  arduboy.fillRect(75,0,64,64,WHITE);

  arduboy.LCDCommandMode();
  SPI.transfer(0x81);  // Set Contrast v
  SPI.transfer(real_brightness);
  SPI.transfer(0xD9);  // Set Precharge
  SPI.transfer(precharge);
  arduboy.LCDDataMode();


arduboy.display();
}


