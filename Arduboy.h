#ifndef Arduboy_h
#define Arduboy_h

#include <SPI.h>
#include <Print.h>
#include <avr/sleep.h>

// EEPROM settings

#define EEPROM_VERSION 0
#define EEPROM_BRIGHTNESS 1
#define EEPROM_AUDIO_ON_OFF 2
// we reserve the first 16 byte of EEPROM for system use
#define EEPROM_STORAGE_SPACE_START 16 // and onward

// eeprom settings above are neded for audio
#include "audio.h"
#include "physics.h"

#define PIXEL_SAFE_MODE
#define SAFE_MODE

#define CS 6
#define DC 4
#define RST 12

#define LEFT_BUTTON _BV(5)
#define RIGHT_BUTTON _BV(3)
#define UP_BUTTON _BV(4)
#define DOWN_BUTTON _BV(2)
#define A_BUTTON _BV(1)
#define B_BUTTON _BV(0)

#define PIN_LEFT_BUTTON 9
#define PIN_RIGHT_BUTTON 5
#define PIN_UP_BUTTON 8
#define PIN_DOWN_BUTTON 10
#define PIN_A_BUTTON A0
#define PIN_B_BUTTON A1

#define WIDTH 128
#define HEIGHT 64

// draw colors
#define WHITE 1
#define BLACK 0
#define TRANSPARENT 255

#define COLUMN_ADDRESS_END (WIDTH - 1) & 0x7F
#define PAGE_ADDRESS_END ((HEIGHT/8)-1) & 0x07


class Arduboy : public Print
{
public:
  Arduboy();

  void start();
  void idle();
  void blank();
  void clearDisplay();
  void display();
  void drawScreen(const unsigned char *image);
  void drawScreen(unsigned char image[]);
  void drawPixel(int x, int y, uint8_t color);
  void drawCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color);
  void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint8_t color);
  void fillCircle(int16_t x0, int16_t y0, int16_t r, uint8_t color);
  void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, int16_t delta, uint8_t color);
  void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint8_t color);
  void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
  void drawFastVLine(int16_t x, int16_t y, int16_t h, uint8_t color);
  void drawFastHLine(int16_t x, int16_t y, int16_t w, uint8_t color);
  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t color);
  void fillScreen(uint8_t color);
  void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint8_t color);
  void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint8_t color);
  void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t color);
  void fillTriangle (int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint8_t color);

  void drawBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint8_t color);
  void drawSlowXYBitmap(int16_t x, int16_t y, const uint8_t *bitmap, int16_t w, int16_t h, uint8_t color);
  void drawChar(int16_t x, int16_t y, unsigned char c, uint8_t color, uint8_t bg, uint8_t size);


  /* drawing setup functions */

  void setCursor(int16_t x, int16_t y);
  void setTextSize(uint8_t s);
  void setTextWrap(boolean w);
  void setColor(uint8_t color);
  void setColor(uint8_t color, uint8_t background);


  /* drawing functions that take physics objects */


  void drawPixel(Point point);
  void drawLine(Point p1, Point p2);
  void erase(Rect rect);
  void drawRect(Rect rect);
  void fillRect(Rect rect);
  void drawRoundRect(Rect rect, int16_t radius);
  void fillRoundRect(Rect rect, int16_t radius);


  /* query methods */

  uint8_t getPixel(uint8_t x, uint8_t y);
  inline unsigned char* getBuffer();
  uint8_t width();
  uint8_t height();


  /* buttons */

  uint8_t getInput();
  boolean pressed(uint8_t buttons);
  boolean not_pressed(uint8_t buttons);


  /* utils */

  void LCDDataMode();
  void LCDCommandMode();
  virtual size_t write(uint8_t);
  void swap(int16_t& a, int16_t& b);

  ArduboyTunes tunes;
  ArduboyAudio audio;

private:
  unsigned char sBuffer[(HEIGHT*WIDTH)/8];

  void bootLCD() __attribute__((always_inline));
  void safeMode() __attribute__((always_inline));
  uint8_t readCapacitivePin(int pinToMeasure);
  uint8_t readCapXtal(int pinToMeasure);
  volatile uint8_t *mosiport, *clkport, *csport, *dcport;
  uint8_t mosipinmask, clkpinmask, cspinmask, dcpinmask;

// Adafruit stuff
protected:
  int8_t drawColor = WHITE;
  int8_t drawBackground = TRANSPARENT;
  int16_t cursor_x = 0;
  int16_t cursor_y = 0;
  uint8_t textsize = 1;
  boolean wrap; // If set, 'wrap' text at right edge of display
};

#endif
