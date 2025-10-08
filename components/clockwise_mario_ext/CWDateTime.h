#pragma once
#include <Arduino.h>

#include "esphome/components/time/real_time_clock.h"

class CWDateTime {
private:
  esphome::time::RealTimeClock* rtc_ = nullptr;  // pointer to the ESPHome RTC
  bool use24hFormat_ = true;

public:
  // Inject the RealTimeClock from ESPHome
  void set_rtc(esphome::time::RealTimeClock *rtc);
  void begin();
  void begin(const char *timeZone, bool use24format, const char *ntpServer, const char *posixTZ);
  String getFormattedTime();
  String getFormattedTime(const char* format);

  char *getHour(const char *format);
  char *getMinute(const char *format);
  int getHour();
  int getMinute();
  int getSecond();
  long getMilliseconds();

  int getDay();
  int getMonth();
  int getWeekday();

  bool isAM();
  bool is24hFormat();
};
