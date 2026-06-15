// Face.h — the H.I.R.O "face": a fully programmatic animated face (no image assets).
// Draws two eyes + a mouth to an off-screen sprite, animates blinking, looking
// around for menu navigation, and a "talking" mouth while music plays.
//
// Everything is drawn into a 16-bit sprite and pushed in one shot, so there's no
// flicker. Tune colours / shapes here to match the look you want.
#pragma once
#include "LGFX_Config.h"

class Face {
public:
  enum class Mood { Idle, Playing, Paused, Browsing };

  explicit Face(LGFX& lcd) : _lcd(lcd), _spr(&lcd) {}

  void begin() {
    _lcd.setRotation(0);              // portrait 240x320; change if mounted rotated
    _lcd.fillScreen(TFT_BLACK);
    _lcd.setBrightness(200);
    _spr.setColorDepth(16);
    _spr.createSprite(_lcd.width(), _lcd.height());
  }

  void setMood(Mood m) { _mood = m; }

  // Nudge the eyes toward a direction (-1..+1) — handy when scrolling a menu.
  void glance(float dir) { _targetGaze = constrain(dir, -1.f, 1.f); }

  // Call every loop; it self-paces with millis().
  void update() {
    uint32_t now = millis();
    if (now - _lastFrame < kFrameMs) return;
    _lastFrame = now;

    // --- blink scheduling ---
    if (now > _nextBlink) { _blinking = true; _blinkStart = now; _nextBlink = now + random(2200, 5200); }
    float lid = 0.f;  // 0 = open, 1 = closed
    if (_blinking) {
      float t = (now - _blinkStart) / float(kBlinkMs);
      if (t >= 1.f) { _blinking = false; lid = 0.f; }
      else          { lid = t < 0.5f ? (t * 2.f) : (2.f - t * 2.f); } // close then open
    }

    // --- gaze easing ---
    _gaze += (_targetGaze - _gaze) * 0.18f;

    // --- mouth animation: "talks" while Playing, flat otherwise ---
    float mouthOpen = 0.15f;
    if (_mood == Mood::Playing) mouthOpen = 0.20f + 0.18f * (0.5f + 0.5f * sinf(now * 0.012f));
    else if (_mood == Mood::Paused) mouthOpen = 0.05f;

    draw(lid, _gaze, mouthOpen);
  }

private:
  void draw(float lid, float gaze, float mouthOpen) {
    const int W = _spr.width(), H = _spr.height();
    _spr.fillSprite(TFT_BLACK);

    const uint16_t eyeColor = _mood == Mood::Paused ? 0x52AA /*dim cyan*/ : 0x07FF /*cyan*/;
    const int cx = W / 2;
    const int eyeY = H * 0.40f;
    const int eyeDX = W * 0.22f;
    const int eyeR  = W * 0.13f;
    const int gazePx = gaze * eyeR * 0.5f;

    drawEye(cx - eyeDX + gazePx, eyeY, eyeR, lid, eyeColor);
    drawEye(cx + eyeDX + gazePx, eyeY, eyeR, lid, eyeColor);

    // mouth: rounded bar that opens/closes
    const int mw = W * 0.34f;
    const int mh = max(4, int(mouthOpen * H * 0.10f));
    const int my = H * 0.66f;
    _spr.fillRoundRect(cx - mw / 2, my - mh / 2, mw, mh, mh / 2, eyeColor);

    _spr.pushSprite(0, 0);
  }

  void drawEye(int x, int y, int r, float lid, uint16_t color) {
    _spr.fillCircle(x, y, r, color);
    _spr.fillCircle(x, y, r * 0.45f, TFT_BLACK);          // pupil
    if (lid > 0.01f) {                                     // eyelid sweeps down
      int h = int(lid * (2 * r + 2));
      _spr.fillRect(x - r - 1, y - r - 1, 2 * r + 2, h, TFT_BLACK);
    }
  }

  static constexpr uint32_t kFrameMs = 33;   // ~30 fps
  static constexpr uint32_t kBlinkMs = 160;

  LGFX&        _lcd;
  LGFX_Sprite  _spr;
  Mood         _mood       = Mood::Idle;
  uint32_t     _lastFrame  = 0;
  uint32_t     _nextBlink  = 1500;
  uint32_t     _blinkStart = 0;
  bool         _blinking   = false;
  float        _gaze = 0.f, _targetGaze = 0.f;
};
