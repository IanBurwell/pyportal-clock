#include "display_task.h"
// #include "consolasregular16pt7b.h" // 15x20
#include "consolasbold100pt7b.h" // 98x129
// #include "consolasbold150pt7b.h" // 146x194 

void DisplayTask::Init(){
    tft_.begin();
    tft_.setRotation(3); // Landscape upright
    tft_.fillScreen(bg_color_);

    int w = dc0_.width(), h = dc0_.height();
    const int hmid = DHEIGHT/2, wgap = 0, hgap = 4;
    tft_.drawBitmap(hmid-h-wgap, hmid-h-hgap, dc0_.getBuffer(), w, h, fg_color_, bg_color_);
    tft_.drawBitmap(hmid-h+w+wgap, hmid-h-hgap, dc1_.getBuffer(), w, h, fg_color_, bg_color_);
    tft_.drawBitmap(hmid-h-wgap, hmid+hgap, dc2_.getBuffer(), w, h, fg_color_, bg_color_);
    tft_.drawBitmap(hmid-h+w+wgap, hmid+hgap, dc3_.getBuffer(), w, h, fg_color_, bg_color_);

    pinMode(TFT_BACKLIGHT, OUTPUT);
    digitalWrite(TFT_BACKLIGHT, HIGH);
    // analogWrite(TFT_BACKLIGHT, 4095/100);
}


void DisplayTask::Update(){
    int w = dc0_.width(), h = dc0_.height();
    const int hmid = DHEIGHT/2, wgap = 0, hgap = 4;
    if(dc0_.setChar('0' + (hrs_%100)/10)){
        tft_.drawBitmap(hmid-h-wgap, hmid-h-hgap, dc0_.getBuffer(), w, h, fg_color_, bg_color_);
    }
    if(dc1_.setChar('0' + hrs_%10)){
        tft_.drawBitmap(hmid-h+w+wgap, hmid-h-hgap, dc1_.getBuffer(), w, h, fg_color_, bg_color_);
    }
    if(dc2_.setChar('0' + (mins_%100)/10)){
        tft_.drawBitmap(hmid-h-wgap, hmid+hgap, dc2_.getBuffer(), w, h, fg_color_, bg_color_);
    }
    if(dc3_.setChar('0' + mins_%10)){
        tft_.drawBitmap(hmid-h+w+wgap, hmid+hgap, dc3_.getBuffer(), w, h, fg_color_, bg_color_);
    }
}
