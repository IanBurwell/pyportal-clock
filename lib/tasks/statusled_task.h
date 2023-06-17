#pragma once

#include <pins.h>
#include <task.h>
#include <Adafruit_NeoPixel.h>
#include <rgb_colors.h>

struct status_flash {
    unsigned int flash_period_ms;
    unsigned int cycle_pause_ms;
    unsigned int number_flashes;
};  

namespace led_state {
    static constexpr status_flash kOff = {0, 0, 0};
    static constexpr status_flash kSolid = {0, 0, 1};
    static constexpr status_flash kSlowFlash = {1000, 0, 1};
    static constexpr status_flash kFastFlash = {250, 0, 1};
    static constexpr status_flash kDoubleFlash = {250, 250, 2};
    static constexpr status_flash kTripleFlash = {250, 250, 3};
}


class StatusLEDTask : public Task {
public:

    StatusLEDTask() : neopixel_(1, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800) {};

    void SetStatusLED(status_flash status);
    void SetRGBLED(uint32_t color);

    void Init() override;
    void Update() override;

private:
    // Status LED vars
    status_flash status_flash_state_ = led_state::kOff;
    int status_current_flash_ = 0;
    unsigned long status_last_state_change_ = 0;
    bool status_led_on_ = false;

    // NeoPixel vars
    Adafruit_NeoPixel neopixel_;
    uint32_t rgb_color_ = color::kBlack;
    bool update_rgb_color_ = false;

};