// LGFX_Config.h — LovyanGFX panel definition for the Waveshare 2.4" ST7789 (240x320)
// on the shared SPI bus. The microSD shares this bus too (see Player.h), so we let
// LovyanGFX own SPI2_HOST and the SD library reuses the same pins/host.
#pragma once

#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "pins.h"

class LGFX : public lgfx::LGFX_Device {
  lgfx::Panel_ST7789  _panel;
  lgfx::Bus_SPI       _bus;
  lgfx::Light_PWM     _light;

public:
  LGFX() {
    { // SPI bus
      auto cfg = _bus.config();
      cfg.spi_host    = SPI2_HOST;   // FSPI on the ESP32-S3
      cfg.spi_mode    = 0;
      cfg.freq_write  = 40000000;    // 40 MHz; drop to 27 MHz if you see glitches on real hw
      cfg.freq_read   = 16000000;
      cfg.spi_3wire   = false;
      cfg.use_lock    = true;        // needed because microSD shares this bus
      cfg.dma_channel = SPI_DMA_CH_AUTO;
      cfg.pin_sclk    = PIN_SPI_SCK;
      cfg.pin_mosi    = PIN_SPI_MOSI;
      cfg.pin_miso    = PIN_SPI_MISO;
      cfg.pin_dc      = PIN_LCD_DC;
      _bus.config(cfg);
      _panel.setBus(&_bus);
    }
    { // ST7789 panel
      auto cfg = _panel.config();
      cfg.pin_cs        = PIN_LCD_CS;
      cfg.pin_rst       = PIN_LCD_RST;
      cfg.pin_busy      = -1;
      cfg.panel_width   = 240;
      cfg.panel_height  = 320;
      cfg.offset_x      = 0;
      cfg.offset_y      = 0;
      cfg.readable      = false;
      cfg.invert        = true;      // ST7789 panels usually need inversion on
      cfg.rgb_order     = false;
      cfg.bus_shared    = true;      // share SPI with the SD card
      _panel.config(cfg);
    }
    { // backlight (PWM so the face can dim / pulse)
      auto cfg = _light.config();
      cfg.pin_bl      = PIN_LCD_BL;
      cfg.invert      = false;
      cfg.freq        = 12000;
      cfg.pwm_channel = 7;
      _light.config(cfg);
      _panel.setLight(&_light);
    }
    setPanel(&_panel);
  }
};
