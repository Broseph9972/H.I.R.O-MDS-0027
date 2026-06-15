// Controls.h — 2 side buttons + EC11 rotary encoder (with push switch).
// All inputs are active-LOW (wired to GND), read with internal pull-ups.
// poll() returns the events that happened since the last call.
#pragma once
#include <Arduino.h>
#include "pins.h"

struct InputEvents {
  bool sw1      = false;   // side button 1  (falling edge)
  bool sw2      = false;   // side button 2
  bool encClick = false;   // encoder push
  int  encDelta = 0;       // detents turned: +cw / -ccw
};

class Controls {
public:
  void begin() {
    pinMode(PIN_BTN_SW1, INPUT_PULLUP);
    pinMode(PIN_BTN_SW2, INPUT_PULLUP);
    pinMode(PIN_ENC_SW,  INPUT_PULLUP);
    pinMode(PIN_ENC_A,   INPUT_PULLUP);
    pinMode(PIN_ENC_B,   INPUT_PULLUP);
    _encState = readAB();
  }

  InputEvents poll() {
    InputEvents ev;
    ev.sw1      = fell(PIN_BTN_SW1, _s1);
    ev.sw2      = fell(PIN_BTN_SW2, _s2);
    ev.encClick = fell(PIN_ENC_SW, _sw);
    ev.encDelta = readEncoder();
    return ev;
  }

private:
  struct Btn { bool last = true; uint32_t t = 0; };

  // Debounced falling-edge detector (true once per press).
  bool fell(uint8_t pin, Btn& b) {
    bool now = digitalRead(pin);
    uint32_t ms = millis();
    if (now != b.last && ms - b.t > 25) {
      b.t = ms;
      bool pressed = (b.last == true && now == false);
      b.last = now;
      return pressed;
    }
    b.last = now;
    return false;
  }

  uint8_t readAB() { return (digitalRead(PIN_ENC_A) << 1) | digitalRead(PIN_ENC_B); }

  // Quadrature decode via transition lookup table; accumulates to whole detents.
  int readEncoder() {
    static const int8_t tbl[16] = {0,-1,1,0, 1,0,0,-1, -1,0,0,1, 0,1,-1,0};
    uint8_t s = readAB();
    int8_t move = tbl[(_encState << 2) | s];
    _encState = s;
    _encAccum += move;
    int detent = 0;
    if (_encAccum >= 4)      { detent =  1; _encAccum = 0; }   // 4 transitions per detent
    else if (_encAccum <= -4){ detent = -1; _encAccum = 0; }
    return detent;
  }

  Btn _s1, _s2, _sw;
  uint8_t _encState = 0;
  int     _encAccum = 0;
};
