#include <SPI.h>
#include "Arduboy.h"
#include "performance.h"


Arduboy display;
Printer output;

int y = 0;

typedef struct benchResult {
  char *name;
  long duration;
};

benchResult runs[16];

void setup() {
  display.start();
}

void benchDrawTriangle()
{
}

void benchFillTriangle()
{
}

void benchPaint()
{
 for (byte i=0; i<64; i++)
  display.display();
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
{}

void benchFillCircle()
{}

void benchDrawPixel()
{
  for (byte x=0; x<128; x++)
    for (byte y=0; y<64; y++) {
      display.drawPixel(x, y, BLACK);
      display.drawPixel(x, y, WHITE);
    }
}

void benchDrawBitmap()
{}

void benchSlowDrawBitmap()
{}


void bench(char *name, void (*func)(), int iters)
{
  long before = micros();
  long after, diff;
  (*func)();
  after = micros();
  diff = after - before;
  ops_per_second = (1000000*iters)/diff
  output.print(name);
  output.print(" ");
  output.printNumber(ops_per_second);
  output.println();
}

void loop () {
  bench("drawPixel", &benchDrawPixel, 8192* 2);
  bench("drawTriangle", &benchDrawTriangle, 0);
  bench("fillTriangle", &benchFillTriangle, 0);
  bench("drawRect", &benchDrawRect, 128+128+64);
  bench("fillRect", &benchFillRect, 128+128+64);
  bench("drawCircle", &benchDrawCircle, 0);
  bench("fillCircle", &benchFillCircle, 0);
  bench("drawRoundRect", &benchDrawRoundRect, 128+128+64);
  bench("fillRoundRect", &benchFillRoundRect, 128+128+64);
  bench("drawLine", &benchDrawLine, 128+128+64);
  bench("drawFastHLine", &benchDrawFastHLine, 64);
  bench("drawFastVLine", &benchDrawFastVLine, 128);
  bench("paint", &benchPaint, 64);
  bench("drawBitmap", &benchDrawBitmap, 0);
  bench("drawSlowBitmap", &benchSlowDrawBitmap, 0);

}
