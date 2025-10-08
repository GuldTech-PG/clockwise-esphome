#include "clockwise_mario.h"
#include <ESP32-HUB75-MatrixPanel-I2S-DMA.h>

// pull the face + engine from third_party
//#include "Clockface.h"
#include "CWDateTime.h"
#include "Locator.h"

namespace clockwise_mario_ext {

static ::CWDateTime g_dt;   // implemented by shim (CWDateTime.cpp)

void MarioClock::setup() {
  HUB75_I2S_CFG cfg(w_, h_, 1);
  cfg.gpio.r1=r1_; cfg.gpio.g1=g1_; cfg.gpio.b1=b1_;
  cfg.gpio.r2=r2_; cfg.gpio.g2=g2_; cfg.gpio.b2=b2_;
  cfg.gpio.a=a_; cfg.gpio.b=bb_; cfg.gpio.c=c_; cfg.gpio.d=d_; cfg.gpio.e=e_;
  cfg.gpio.lat=lat_; cfg.gpio.oe=oe_; cfg.gpio.clk=clk_;
  cfg.clkphase = clkphase_;
  if (driver_=="FM6126A") cfg.driver = HUB75_I2S_CFG::FM6126A;

  panel_ = new MatrixPanel_I2S_DMA(cfg);
  panel_->begin();
  panel_->setBrightness8(brightness_);
  panel_->clearScreen();

  // Provide Adafruit_GFX* to the Clockwise gfx engine (via Locator)
  Locator::provide(panel_);

  // The two lines from Clockwise main.cpp (face construction & setup)
  g_dt.begin();               // shim; delegates to ESPHome time
  g_dt.set_rtc(time_);
 
  clockface_ = new Clockface(static_cast<Adafruit_GFX*>(panel_));
  clockface_->setup(&g_dt);
}

void MarioClock::update() {
  if (clockface_) clockface_->update(); // just like Clockwise's loop
}

} // namespace clockwise_mario_ext
