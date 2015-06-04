#include "Arduboy.h"


// store current and previous buttons state for frame based button events
// you should be using nextFrame() in almost all cases, not calling this
// directly
void Arduboy::pollButtons()
{
  previousButtonState = currentButtonState;
  currentButtonState = getInput();
}

// returns true if the button mask passed in is pressed
//
//   if (pressed(LEFT_BUTTON + A_BUTTON))
boolean Arduboy::pressed(uint8_t buttons)
{
 // LEGACY: handle apps not using frames
 if (frameCount == 0)
   currentButtonState = getInput();

 return (currentButtonState & buttons) == buttons;
}

// returns true if a button that has been held down was just released
// this function only reliably works with a single button. You should not
// pass it multiple buttons as you can with some of the other button
// functions.
//
// This can be used for confirmations or other times when you want to take
// an action AFTER the user finishes the pressing rather than immediately
// when the button goes down.  Not that there is any good way for someone
// to change their mind, but the experience can feel very different.
boolean Arduboy::justReleased(uint8_t button)
{
 return ((previousButtonState & button) && !(currentButtonState & button));
}

// returns true if a button has just been pressed
// if the button has been held down for multiple frames this will return
// false.  You should only use this to poll a single button.
boolean Arduboy::justPressed(uint8_t button)
{
 return (!(previousButtonState & button) && (currentButtonState & button));
}

// returns true if the button mask passed in not pressed
//
//   if (not_pressed(LEFT_BUTTON))
boolean Arduboy::not_pressed(uint8_t buttons)
{
  // LEGACY: handle apps not using frames
  if (frameCount == 0)
    currentButtonState = getInput();
  return (currentButtonState & buttons) == 0;
}


uint8_t Arduboy::getInput()
{
  // b00lurdab
  uint8_t buttons = B00000000;

  if (!digitalRead(PIN_LEFT_BUTTON)) { buttons |= LEFT_BUTTON; }  // left
  if (!digitalRead(PIN_RIGHT_BUTTON)) { buttons |= RIGHT_BUTTON; }  // right
  if (!digitalRead(PIN_UP_BUTTON)) { buttons |= UP_BUTTON; }  // up
  if (!digitalRead(PIN_DOWN_BUTTON)) { buttons |= DOWN_BUTTON; }  // down
  if (!digitalRead(PIN_A_BUTTON)) { buttons |= A_BUTTON; }  // a?
  if (!digitalRead(PIN_B_BUTTON)) { buttons |= B_BUTTON; }  // b?
  return buttons;
}
