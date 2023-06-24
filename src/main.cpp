#ifdef TARGET_NATIVE
    int main(){return 0;} // Make native build happy
#else

#include <Arduino.h>
#include <logger.h>
#include <scheduler.h>
#include <statusled_task.h>


Scheduler sched;
StatusLEDTask led_task;
Logger& logger = Logger::Instance();

void setup() {
    led_task.SetStatusLED(led_state::kSlowFlash);
    led_task.SetRGBLED(color::kGreen);

    sched.ScheduleTask("LEDTask", 0, led_task);
    logger.Info("setup complete");
}

void loop() {
    sched.Tick();
}

#endif