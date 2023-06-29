#pragma once

#include <task.h>
#include <pins.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_HX8357.h>
#include "clock_digit_canvas.h"

#define DWIDTH 480
#define DHEIGHT 320

class DisplayTask : public Task {
public:
    void Init() override;
    void Update() override;

    DisplayTask() : tft_(tft8bitbus, TFT_D0, TFT_WR, TFT_DC, TFT_CS, TFT_RST, TFT_RD){};

    void SetHours(int hours){ hrs_ = hours; };
    void SetMinutes(int minutes){ mins_ = minutes; };
    void SetSeconds(int seconds){ secs_ = seconds; };

    /// 0-4095
    void SetBrightness(int brightness){ analogWrite(TFT_BACKLIGHT, brightness); };

private:
    Adafruit_HX8357 tft_;
    ClockDigitCanvas dc0_, dc1_, dc2_, dc3_;

    int hrs_ = 12, mins_ = 34, secs_ = 56;

    uint16_t fg_color_ = HX8357_WHITE;
    uint16_t bg_color_ = HX8357_RED;

};