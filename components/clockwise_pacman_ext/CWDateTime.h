#pragma once
#include <Arduino.h>

#ifdef ESPHOME_VERSION
  #include "esphome/components/time/real_time_clock.h"
#else
  #include <ezTime.h>
  #include <WiFi.h>
#endif

class CWDateTime {
private:
#ifdef ESPHOME_VERSION
  esphome::time::RealTimeClock *rtc_ = nullptr;
#else
  Timezone myTZ;
#endif
  bool use24hFormat_ = true;

public:
#ifdef ESPHOME_VERSION
  void begin(esphome::time::RealTimeClock *rtc);
#else
  void begin(const char *timeZone, bool use24format, const char *ntpServer, const char *posixTZ);
#endif
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
