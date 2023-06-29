#ifdef TARGET_NATIVE
    int main(){return 0;} // Make native build happy
#else

#include <Arduino.h>
#include <logger.h>
#include <scheduler.h>
#include <statusled_task.h>
#include <sdcard_task.h>
#include <display_task.h>


Scheduler sched;
SDCardTask sd_task;
StatusLEDTask led_task;
DisplayTask display_task;

Logger& logger = Logger::Instance();

void setup() {
    delay(2000);
    logger.Info("Initializing");

    led_task.SetStatusLED(led_state::kSlowFlash);
    led_task.SetRGBLED(color::kGreen);
    
    // NOTE: Initializing SD before the display causes issues for some reason
    sched.ScheduleTask("DisplayTask", 100, display_task);
    sched.ScheduleTask("SDTask", 1, sd_task);
    sched.ScheduleTask("LEDTask", 0, led_task);

    logger.Info("Setup complete");
}

void loop() {
    sched.Tick();
}

#endif