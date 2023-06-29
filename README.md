![PlatformIO CI](https://github.com/IanBurwell/pyportal[]clock/actions/workflows/pio.yml/badge.svg)

A project using a PyPortal Titano to create a useful bedside alarm clock


### TODO
- [ ] Create/find logger library
  - [x] Log with levels
  - [x] Log to SD card
  - [ ] Log buffer overflow detection
  - [ ] Add printf functionality
- [ ] Access files on SD card
- [ ] Configure display
  - [ ] Make basic clock display
  - [ ] Decrease brightness [PWM noise](https://github.com/adafruit/circuitpython/pull/6416)
  - [ ] Set brightness with light sensor
  - [ ] Create architecture to support multiple screens
- [ ] Play SD sounds on speaker
- [ ] Interface with ESP32 Airlift
  - [ ] Create/explore a secrets file
  - [ ] Request weather
- [ ] Interface with I2C NeoKey
- [ ] Interface with I2C temp sensor
- [ ] Scheduler improvements
  - [ ] Add time usage tracking/logging
  - [ ] Handle millis wrap around (~50 days)
- [ ] Explore PlatformIO remote development
- [ ] Improve `pin.h` 
  - [ ] Is it the best way to handle pindefs?
  - [ ] Fill in more if so
- [ ] Improve StatusLEDTask to include RAINBOW
  - [ ] Write Tests (heh)
- [ ] Support Base PyPortal
- [ ] Create clock digit font with only required digits