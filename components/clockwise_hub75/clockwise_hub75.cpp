#include "clockwise_hub75.h"
#include "esphome/core/log.h"

namespace esphome {
namespace clockwise_hub75 {

static const char *const TAG = "clockwise_hub75";

void ClockwiseHUB75::setup() {
  ESP_LOGCONFIG(TAG, "Setting up Clockwise HUB75 Integration...");
  
  if (hub75_display_ == nullptr) {
    ESP_LOGE(TAG, "HUB75 display pointer not set (codegen failed to inject). Aborting setup.");
    return;
  }
  
  // Set initial state
  current_brightness_ = initial_brightness_;
  hub75_display_->set_brightness(current_brightness_);
  
  ESP_LOGCONFIG(TAG, "Clockwise HUB75 setup complete");
}

void ClockwiseHUB75::loop() {
  uint32_t now = millis();
  
  // Update display every second for clock functionality
  if (now - last_update_ >= 1000) {
    last_update_ = now;
    update_display_();
  }
}

void ClockwiseHUB75::dump_config() {
  ESP_LOGCONFIG(TAG, "Clockwise HUB75:");
  ESP_LOGCONFIG(TAG, "  Clockface Type: %d", static_cast<int>(clockface_type_));
  ESP_LOGCONFIG(TAG, "  Initial Brightness: %d", initial_brightness_);
  ESP_LOGCONFIG(TAG, "  Current Brightness: %d", current_brightness_);
  ESP_LOGCONFIG(TAG, "  Power State: %s", YESNO(power_state_));
}

void ClockwiseHUB75::set_brightness(uint8_t brightness) {
  current_brightness_ = brightness;
  if (hub75_display_ != nullptr) {
    hub75_display_->set_brightness(brightness);
  }
  ESP_LOGD(TAG, "Brightness set to %d", brightness);
}

void ClockwiseHUB75::set_power(bool state) {
  power_state_ = state;
  if (hub75_display_ != nullptr) {
    if (state) {
      hub75_display_->set_brightness(current_brightness_);
    } else {
      hub75_display_->set_brightness(0);
    }
  }
  ESP_LOGD(TAG, "Power state set to %s", YESNO(state));
}

void ClockwiseHUB75::switch_clockface(ClockfaceType type) {
  clockface_type_ = type;
  ESP_LOGD(TAG, "Clockface switched to %d", static_cast<int>(type));
  update_display_();
}

void ClockwiseHUB75::update_display_() {
  if (!power_state_ || hub75_display_ == nullptr) {
    return;
  }
  
  // Clear the display (fill with black)
  hub75_display_->fill(Color(0,0,0));
  
  // Render the appropriate clockface
  switch (clockface_type_) {
    case PACMAN:
      render_pacman_clockface_();
      break;
    case MARIO:
      render_mario_clockface_();
      break;
    case CLOCK:
      render_clock_clockface_();
      break;
  }
}

void ClockwiseHUB75::render_pacman_clockface_() {
  // TODO: Implement Pacman clockface rendering
  // This will use the existing pacman logic adapted for HUB75
  
  // Full-screen test pattern to verify 64×64 display
  int width = hub75_display_->get_width();
  int height = hub75_display_->get_height();
  
  // Draw gradient test pattern across full display
  for (int x = 0; x < width; x++) {
    for (int y = 0; y < height; y++) {
      // Create RGB gradient based on position
      uint8_t r = (x * 255) / width;
      uint8_t g = (y * 255) / height;
      uint8_t b = ((x + y) * 255) / (width + height);
      hub75_display_->draw_pixel_at(x, y, Color(r, g, b));
    }
  }
  
  // Draw white border to confirm edges
  for (int x = 0; x < width; x++) {
    hub75_display_->draw_pixel_at(x, 0, Color(255, 255, 255));
    hub75_display_->draw_pixel_at(x, height - 1, Color(255, 255, 255));
  }
  for (int y = 0; y < height; y++) {
    hub75_display_->draw_pixel_at(0, y, Color(255, 255, 255));
    hub75_display_->draw_pixel_at(width - 1, y, Color(255, 255, 255));
  }
}

void ClockwiseHUB75::render_mario_clockface_() {
  // TODO: Implement Mario clockface rendering
  // This will use the existing mario logic adapted for HUB75
  
  // For now, just draw a simple test pattern
  auto red = Color(255, 0, 0);
  auto blue = Color(0, 0, 255);
  
  // Draw Mario-style pattern as placeholder
  for (int x = 8; x < 16; x++) {
    for (int y = 0; y < 8; y++) {
      if ((x + y) % 2 == 0) {
        hub75_display_->draw_pixel_at(x, y, red);
      } else {
        hub75_display_->draw_pixel_at(x, y, blue);
      }
    }
  }
}

void ClockwiseHUB75::render_clock_clockface_() {
  // TODO: Implement basic clock rendering
  
  // For now, just draw a simple digital time display
  auto white = Color(255, 255, 255);
  
  // Draw a simple clock pattern as placeholder
  for (int x = 16; x < 24; x++) {
    for (int y = 0; y < 8; y++) {
      if (x == 20 || y == 4) {  // Simple cross pattern
        hub75_display_->draw_pixel_at(x, y, white);
      }
    }
  }
}

}  // namespace clockwise_hub75
}  // namespace esphome