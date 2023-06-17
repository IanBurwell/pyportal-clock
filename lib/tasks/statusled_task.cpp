#include <Arduino.h>
#include "statusled_task.h"

void StatusLEDTask::SetStatusLED(status_flash status){
    status_flash_state_ = status;
    status_current_flash_ = 0;
    status_last_state_change_ = millis();
    status_led_on_ = false;
    digitalWrite(STATUS_LED_PIN, LOW);
}


void StatusLEDTask::SetRGBLED(uint32_t color){
    rgb_color_ = color;
    update_rgb_color_ = true;
}


void StatusLEDTask::Init(){
    pinMode(STATUS_LED_PIN, OUTPUT);
    digitalWrite(STATUS_LED_PIN, LOW);

    neopixel_.begin();
}


void StatusLEDTask::Update(){
    // Update the RGB LED if we have a new color
    if(update_rgb_color_){
        neopixel_.setPixelColor(0, rgb_color_);
        neopixel_.show();
        update_rgb_color_ = false;
    }

    // Update Status LED
    // Wait longer on the first pause by adding cycle_pause_ms
    unsigned int wait_time = status_flash_state_.flash_period_ms;
    if(status_current_flash_ == 0 && !status_led_on_ )
        wait_time += status_flash_state_.cycle_pause_ms;
    // Change state if more than wait_time ms have passed
    unsigned long now = millis();
    if(now-status_last_state_change_ > wait_time){
        status_led_on_ = !status_led_on_;
        digitalWrite(STATUS_LED_PIN, status_led_on_);

        if(!status_led_on_)
            status_current_flash_ = (status_current_flash_+1) % status_flash_state_.number_flashes;
        
        status_last_state_change_ = now;
    }
}
