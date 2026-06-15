// main.cpp — H.I.R.O MDS-0027 firmware entry point.
//
// Controls:
//   • Encoder turn  -> volume
//   • Encoder click -> play / pause
//   • Side button 1 -> previous track
//   • Side button 2 -> next track
//   • Hold button 1 -> toggle speaker / headphone output
//
// First bring-up order on real hardware: (1) screen shows a face, (2) SD mounts &
// lists tracks over serial, (3) audio plays to the speaker. Tackle them in that order.
#include <Arduino.h>
#include "LGFX_Config.h"
#include "Face.h"
#include "Player.h"
#include "Controls.h"

static LGFX     lcd;
static Face     face(lcd);
static Player   player;
static Controls controls;

Player* gPlayer = nullptr;   // for the audio end-of-file callback below

// ESP32-audioI2S fires this when a track finishes -> auto-advance.
void audio_eof_mp3(const char* info) { if (gPlayer) gPlayer->onTrackEnd(); }

void setup() {
  Serial.begin(115200);
  delay(200);
  Serial.println("\nH.I.R.O MDS-0027 booting...");

  face.begin();                 // brings up the display + draws the face
  controls.begin();

  gPlayer = &player;
  if (player.begin() && player.trackCount() > 0) {
    player.playIndex(0);        // kick off the first track so there's something to hear
  } else {
    Serial.println("[main] No SD / no tracks — running face-only.");
  }
}

void loop() {
  player.loop();                // MUST run often to keep audio fed

  InputEvents ev = controls.poll();
  if (ev.encDelta > 0)      { player.volumeUp();   face.glance(0.6f); }
  else if (ev.encDelta < 0) { player.volumeDown(); face.glance(-0.6f); }
  if (ev.encClick)          { player.togglePause(); }
  if (ev.sw1)               { player.prev(); face.glance(-1.f); }
  if (ev.sw2)               { player.next(); face.glance(1.f); }

  // Hold SW1 (~700 ms) -> swap speaker/headphone.
  static uint32_t sw1Down = 0;
  if (digitalRead(PIN_BTN_SW1) == LOW) {
    if (!sw1Down) sw1Down = millis();
    else if (millis() - sw1Down > 700) { player.toggleOutput(); sw1Down = 0; }
  } else sw1Down = 0;

  // Reflect playback state on the face.
  if (player.isPaused())      face.setMood(Face::Mood::Paused);
  else if (player.isActive()) face.setMood(Face::Mood::Playing);
  else                        face.setMood(Face::Mood::Idle);

  face.update();                // self-paced ~30 fps, non-blocking
}
