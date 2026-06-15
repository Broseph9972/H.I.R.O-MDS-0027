// pins.h — H.I.R.O MDS-0027 pin map
// These come straight from the verified KiCad schematic (Pcb/hiro.kicad_sch).
// If you ever re-route the board, update these to match.
#pragma once

// ---- I2S audio (shared bit/word clock; one data line per DAC) ----
#define PIN_I2S_BCLK   39   // bit clock  -> MAX98357A + PCM5102A
#define PIN_I2S_LRCK   40   // word/LR clock -> both
#define PIN_I2S_DOUT_SPK  9    // data -> MAX98357A (built-in speaker)
#define PIN_I2S_DOUT_HP   38   // data -> PCM5102A (3.5mm headphone jack)

// ---- Shared SPI bus (display + microSD) ----
#define PIN_SPI_SCK    7
#define PIN_SPI_MOSI   11
#define PIN_SPI_MISO   12

// ---- ST7789 2.4" display (Waveshare, 240x320) ----
#define PIN_LCD_CS     8
#define PIN_LCD_DC     44
#define PIN_LCD_RST    5
#define PIN_LCD_BL     6    // backlight (PWM-dimmable)

// ---- microSD card ----
#define PIN_SD_CS      13

// ---- Controls (all active-LOW; wired button -> GND, use INPUT_PULLUP) ----
#define PIN_BTN_SW1    3    // side button 1
#define PIN_BTN_SW2    42   // side button 2
#define PIN_ENC_SW     4    // rotary encoder push (was "SW3")
#define PIN_ENC_A      1    // encoder quadrature A
#define PIN_ENC_B      2    // encoder quadrature B
