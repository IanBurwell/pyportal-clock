#include <Adafruit_GFX.h>

#include "consolasbold100pt7b.h" // 98x129


class ClockDigitCanvas : public GFXcanvas1 {
public:
    ClockDigitCanvas() : GFXcanvas1(98, 129) {
        setFont(&Consolas_Bold100pt7b);
        setTextWrap(false);
        setChar(' ');
    };

    bool setChar(char c){
        // Dont redraw if the same digit
        if(current_digit_ == c)
            return false;
        // Draw digit
        current_digit_ = c;
        fillScreen(0);
        setCursor(-5, 126);
        print(c);
        return true;
    }

private:
    char current_digit_{};

};