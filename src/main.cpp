#ifdef TARGET_NATIVE
    int main(){return 0;} // Make native build happy
#else

#include <Arduino.h>

void setup() {
    pinMode(13, OUTPUT);
}

void loop() {
    digitalWrite(13, !digitalRead(13));
    delay(200);
}

#endif