# H.I.R.O Firmware

Firmware for the H.I.R.O MDS-0027 MP3 player (Seeed XIAO ESP32-S3 Plus).

## Build & flash

1. Install **VS Code** + the **PlatformIO IDE** extension.
2. Open this `Firmware/` folder in VS Code (PlatformIO detects `platformio.ini`).
3. Plug in the XIAO over USB-C → click **Upload** (the ✓→ arrow in the PlatformIO toolbar).
4. Open the **Serial Monitor** (115200 baud) to watch boot / SD logs.

## SD card

- Format **FAT32**.
- Put your music in a top-level `/music` folder.
- Supported: **MP3, AAC, M4A, FLAC, WAV, OGG/Vorbis, Opus**.

## Controls

| Input | Action |
|-------|--------|
| Encoder turn | Volume |
| Encoder click | Play / Pause |
| Side button 1 | Previous track |
| Side button 2 | Next track |
| Hold side button 1 (~0.7 s) | Toggle speaker ↔ headphone |

## Code map

| File | Purpose |
|------|---------|
| `src/pins.h` | Pin map (matches the KiCad schematic — single source of truth) |
| `src/LGFX_Config.h` | ST7789 display config (LovyanGFX) |
| `src/Face.h` | Programmatic animated face |
| `src/Player.h` | SD playlist + audio decode + I²S output routing |
| `src/Controls.h` | Buttons + rotary encoder |
| `src/main.cpp` | Wires it all together |

## First-hardware bring-up notes

This compiles, but it has **never run on the real board** (the board doesn't exist yet). Expect to iterate on:

1. **SPI bus sharing (display + SD).** They share SCK/MOSI/MISO. If the screen garbles during card reads, lower `freq_write` in `LGFX_Config.h` and/or the SD clock in `Player.h`.
2. **Display orientation / colors.** `setRotation`, `invert`, and `rgb_order` may need flipping once you can see it.
3. **Speaker/headphone switch.** With no jack-detect wired, output is swapped manually (hold SW1). Verify both DACs sound right.
4. **Button polarity / encoder direction.** If the encoder counts backwards, swap `PIN_ENC_A`/`PIN_ENC_B`.
