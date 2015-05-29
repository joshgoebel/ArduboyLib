#include <SPI.h>
#include "Arduboy.h"
#include "performance.h"
#include "graphics.h"


Arduboy display;
Printer output;

int y = 0;

typedef struct benchResult {
  char *name;
  long duration;
};

benchResult runs[16];

void benchDrawTriangle()
{
}

void benchFillTriangle()
{
}

void benchDrawLine()
{
  int x = 0, y = 0;
  for (x=0; x<128; x++)
    display.drawLine(0, 127, x, y, WHITE);
  for (y=0; y<64; y++)
    display.drawLine(0, 127, x, y, WHITE);
  for (x=127; x>0; x--)
    display.drawLine(0, 127, x, y, WHITE);
}

void benchDrawFastHLine()
{
  for (byte y=0; y<64; y++)
    display.drawFastHLine(0, y, 127, WHITE);
}

void benchDrawFastVLine()
{
 for (byte x=0; x<128; x++)
   display.drawFastVLine(x, 0, 63, WHITE);
}

void benchDrawRect()
{
  int x = 0, y = 0;
  for (x=0; x<128; x++)
    display.drawRect(0, 0, x, y, WHITE);
  for (y=0; y<64; y++)
    display.drawRect(0, 0, x, y, WHITE);
  for (x=127; x>0; x--)
    display.drawRect(0, 0, x, y, WHITE);
}

void benchFillRect()
{
  int x = 0, y = 0;
  for (x=0; x<128; x++)
    display.fillRect(0, 0, x, y, WHITE);
  for (y=0; y<64; y++)
    display.fillRect(0, 0, x, y, WHITE);
  for (x=127; x>0; x--)
    display.fillRect(0, 0, x, y, WHITE);
}

void benchDrawRoundRect()
{
  int x = 0, y = 0;

  for (x=0; x<128; x++)
    display.drawRoundRect(0, 0, x, y, 5, WHITE);
  for (y=0; y<64; y++)
    display.drawRoundRect(0, 0, x, y, 5, WHITE);
  for (x=127; x>0; x--)
    display.drawRoundRect(0, 0, x, y, 5, WHITE);
}

void benchFillRoundRect()
{
  int x = 0, y = 0;
  for (x=0; x<128; x++)
    display.fillRoundRect(0, 0, x, y, 5,WHITE);
  for (y=0; y<64; y++)
    display.fillRoundRect(0, 0, x, y, 5,WHITE);
  for (x=127; x>0; x--)
    display.fillRoundRect(0, 0, x, y, 5,WHITE);

}

void benchDrawCircle()
{
  int x = 0, y = 0;
  for (byte x=0; x<128; x++)
    for (byte y=0; y<64; y++) {
      display.drawCircle(x, y, x%64, WHITE);
      display.drawCircle(x, y, x%64, BLACK);
    }
}

void benchFillCircle()
{
  int x = 0, y = 0;
  for (byte x=0; x<128; x++)
    for (byte y=0; y<64; y++) {
      display.fillCircle(x, y, x%64, WHITE);
      display.fillCircle(x, y, x%64, BLACK);
    }
}

void benchDrawPixel()
{
  for (byte x=0; x<128; x++)
    for (byte y=0; y<64; y++) {
      display.drawPixel(x, y, BLACK);
      display.drawPixel(x, y, WHITE);
    }
}

void benchDrawBitmap()
{
  // start drawing half way offscreen
  int x = -32, y=-16;
  int ox = 0, oy = 0;
  for (byte ox=0; ox<128; ox++) {
    for (byte oy=0; oy<64; oy++) {
      display.drawBitmap(ox, oy, megaman_bg,32,64,WHITE);
    }
  }
}

void benchSlowDrawBitmap()
{
  // start drawing half way offscreen
  int x = -32, y=-16;
  int ox = 0, oy = 0;
  for (byte ox=0; ox<128; ox++) {
    for (byte oy=0; oy<64; oy++) {
      // this won't render correctly, but we're not looking at it so
      // we shouldn't care
      display.drawSlowXYBitmap(ox, oy, megaman_bg,32,64,WHITE);
    }
  }
}

void benchPaint()
{
 for (byte i=0; i<256; i++)
  display.display();
}


void bench(char *name, void (*func)(), int iters)
{
  long before = micros();
  long after, diff;
  long ops_per_second;
  (*func)();
  after = micros();
  diff = after - before;
  ops_per_second = ((long)1000000*iters)/diff;
  output.print(name);
  output.print(" ");
  output.print(ops_per_second, 10);
  output.println();
}

void setup() {
  display.start();

  output = Printer(&display);

  bench("drawPixel", &benchDrawPixel, 8192* 2);
  bench("drawTriangle", &benchDrawTriangle, 0);
  bench("fillTriangle", &benchFillTriangle, 0);
  bench("drawRect", &benchDrawRect, 128+128+64);
  bench("fillRect", &benchFillRect, 128+128+64);
  bench("drawCircle", &benchDrawCircle, 8192);
  bench("fillCircle", &benchFillCircle, 8192);
  bench("drawRoundRect", &benchDrawRoundRect, 128+128+64);
  bench("fillRoundRect", &benchFillRoundRect, 128+128+64);
  bench("drawLine", &benchDrawLine, 128+128+64);
  bench("drawFastHLine", &benchDrawFastHLine, 64);
  bench("drawFastVLine", &benchDrawFastVLine, 128);
  bench("drawBitmap", &benchDrawBitmap, 8192);
  bench("drawSlowBitmap", &benchSlowDrawBitmap, 8192);
  display.clearDisplay();
  bench("paint", &benchPaint, 256);
}



void loop () {
  // scroll
  if (display.pressed(DOWN_BUTTON)) {
    output.offset = max(MAX_OFFSET, output.offset+1);
  } else if (display.pressed(UP_BUTTON)) {
    output.offset = min(0, output.offset-1);
  }

  display.clearDisplay();
  output.paint();

  delay(50);
}
