// Player.h — microSD music playback via ESP32-audioI2S (MP3/AAC/M4A/FLAC/WAV/OGG/Opus).
// Builds a playlist from /music on the card and pushes decoded audio over I2S to
// either the built-in speaker amp (MAX98357A) or the headphone DAC (PCM5102A).
//
// NOTE: the SD card SHARES the SPI bus with the display. The single most likely
// bring-up issue on real hardware is SPI bus contention — if the screen garbles
// while the card reads, lower the LovyanGFX freq_write and/or the SD clock below.
#pragma once
#include <Arduino.h>
#include <vector>
#include <SD.h>
#include <SPI.h>
#include "Audio.h"
#include "pins.h"

class Player {
public:
  enum class Output { Speaker, Headphone };

  bool begin() {
    // Shared SPI bus instance (display already configured SPI2_HOST/FSPI on these pins).
    _spi.begin(PIN_SPI_SCK, PIN_SPI_MISO, PIN_SPI_MOSI, PIN_SD_CS);
    if (!SD.begin(PIN_SD_CS, _spi, 20000000)) {   // 20 MHz; lower to 8–10 MHz if flaky
      Serial.println("[Player] SD card init FAILED");
      return false;
    }
    setOutput(Output::Speaker);
    _audio.setVolume(_volume);                     // 0..21
    scan("/music");
    Serial.printf("[Player] %u track(s) found\n", (unsigned)_playlist.size());
    return true;
  }

  // Route audio to the speaker amp or the headphone DAC (shared clocks, swap data pin).
  void setOutput(Output o) {
    _output = o;
    int dout = (o == Output::Speaker) ? PIN_I2S_DOUT_SPK : PIN_I2S_DOUT_HP;
    _audio.setPinout(PIN_I2S_BCLK, PIN_I2S_LRCK, dout);
  }
  void toggleOutput() { setOutput(_output == Output::Speaker ? Output::Headphone : Output::Speaker); }

  void loop() { _audio.loop(); }

  void playIndex(int i) {
    if (_playlist.empty()) return;
    _index = (i % (int)_playlist.size() + _playlist.size()) % _playlist.size();
    Serial.printf("[Player] play: %s\n", _playlist[_index].c_str());
    _audio.connecttoFS(SD, _playlist[_index].c_str());
    _paused = false;
  }
  void next()  { playIndex(_index + 1); }
  void prev()  { playIndex(_index - 1); }

  void togglePause() {
    if (!isActive()) { playIndex(_index); return; }
    _audio.pauseResume();
    _paused = !_paused;
  }

  void volumeUp()   { setVolume(_volume + 1); }
  void volumeDown() { setVolume(_volume - 1); }
  void setVolume(int v) { _volume = constrain(v, 0, 21); _audio.setVolume(_volume); }

  bool isActive() const { return const_cast<Audio&>(_audio).isRunning(); }
  bool isPaused() const { return _paused; }
  int  volume()   const { return _volume; }
  size_t trackCount() const { return _playlist.size(); }

  // Called from the library's end-of-file callback (see main.cpp) — auto-advance.
  void onTrackEnd() { next(); }

private:
  void scan(const char* dir) {
    _playlist.clear();
    File d = SD.open(dir);
    if (!d || !d.isDirectory()) { Serial.printf("[Player] no %s dir\n", dir); return; }
    for (File f = d.openNextFile(); f; f = d.openNextFile()) {
      if (!f.isDirectory() && isAudio(f.name())) _playlist.push_back(String(dir) + "/" + f.name());
      f.close();
    }
    std::sort(_playlist.begin(), _playlist.end());
  }

  static bool isAudio(const char* name) {
    String n = String(name); n.toLowerCase();
    const char* ext[] = {".mp3",".aac",".m4a",".flac",".wav",".ogg",".opus"};
    for (auto e : ext) if (n.endsWith(e)) return true;
    return false;
  }

  Audio                 _audio;
  SPIClass              _spi{FSPI};
  std::vector<String>   _playlist;
  int                   _index   = 0;
  int                   _volume  = 12;
  bool                  _paused  = false;
  Output                _output  = Output::Speaker;
};
