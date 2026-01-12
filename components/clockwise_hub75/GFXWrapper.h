#pragma once
#include <Adafruit_GFX.h>
#include "esphome/components/hub75/hub75_component.h"

// Adapter to make HUB75Display compatible with Adafruit_GFX-based code
class GFXWrapper : public Adafruit_GFX {
 public:
  GFXWrapper(esphome::hub75::HUB75Display *display)
      : Adafruit_GFX(display->get_width(), display->get_height()), display_(display) {}
  
  void drawPixel(int16_t x, int16_t y, uint16_t color) override {
    // Apply rotation transformation manually
    int16_t t;
    switch (rotation) {
      case 1:  // 90° clockwise
        t = x;
        x = WIDTH - 1 - y;
        y = t;
        break;
      case 2:  // 180°
        x = WIDTH - 1 - x;
        y = HEIGHT - 1 - y;
        break;
      case 3:  // 270° clockwise
        t = x;
        x = y;
        y = HEIGHT - 1 - t;
        break;
    }
    
    // Bounds check after rotation
    if ((x < 0) || (x >= width()) || (y < 0) || (y >= height())) {
      return;
    }
    
    // Convert RGB565 to RGB888
    // Note: Adafruit_GFX RGB565 is actually BGR order, so we swap R and B
    uint8_t b = ((color >> 11) & 0x1F) << 3;  // Blue from high bits
    uint8_t g = ((color >> 5) & 0x3F) << 2;   // Green from middle bits
    uint8_t r = (color & 0x1F) << 3;          // Red from low bits
    display_->draw_pixel_at(x, y, esphome::Color(r, g, b));
  }
  
  void fillScreen(uint16_t color) {
    // Convert RGB565 to RGB888
    uint8_t b = ((color >> 11) & 0x1F) << 3;
    uint8_t g = ((color >> 5) & 0x3F) << 2;
    uint8_t r = (color & 0x1F) << 3;
    display_->fill(esphome::Color(r, g, b));
  }
  
 private:
  esphome::hub75::HUB75Display *display_;
};
