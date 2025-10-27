#pragma once

#include "esphome/core/component.h"
#include "esphome/components/hub75/hub75_component.h"  // ensure path matches upstream; if build fails may need to adjust

namespace esphome {
namespace clockwise_hub75 {

enum ClockfaceType {
    PACMAN = 0,
    MARIO = 1,
    CLOCK = 2
};

class ClockwiseHUB75 : public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::AFTER_CONNECTION; }

  // Configuration
  void set_hub75_display(hub75_display::HUB75Display *display) { hub75_display_ = display; }
  void set_clockface_type(ClockfaceType type) { clockface_type_ = type; }
  void set_initial_brightness(uint8_t brightness) { initial_brightness_ = brightness; }

  // Control methods for Home Assistant
  void set_brightness(uint8_t brightness);
  void set_power(bool state);
  void switch_clockface(ClockfaceType type);
  
  // Getters for entities
  uint8_t get_brightness() const { return current_brightness_; }
  bool get_power() const { return power_state_; }
  ClockfaceType get_clockface_type() const { return clockface_type_; }

 protected:
  hub75_display::HUB75Display *hub75_display_{nullptr};
  
  ClockfaceType clockface_type_{PACMAN};
  uint8_t initial_brightness_{128};
  uint8_t current_brightness_{128};
  bool power_state_{true};
  
  uint32_t last_update_{0};
  
  void update_display_();
  void render_pacman_clockface_();
  void render_mario_clockface_();
  void render_clock_clockface_();
};

}  // namespace clockwise_hub75
}  // namespace esphome