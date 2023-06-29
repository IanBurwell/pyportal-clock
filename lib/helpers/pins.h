// https://cdn-learn.adafruit.com/assets/assets/000/111/879/original/adafruit_products_Adafruit_PyPortal_Titano_Pinout.png
#pragma once
#include <variant.h>

// LEDs
#define STATUS_LED_PIN LED_BUILTIN
#define NEOPIXEL_PIN   02u

// SD Card
#define SD_CS_PIN      32u
#define SD_DETECT_PIN  33u
#define SD_MOSI_PIN    PIN_SPI_MOSI
#define SD_MISO_PIN    PIN_SPI_MISO
#define SD_SCK_PIN     PIN_SPI_SCK

// TFT display (HX8357)
#define TFT_D0        34 // Data bit 0 pin (MUST be on PORT byte boundary)
#define TFT_WR        26 // Write-strobe pin (CCL-inverted timer output)
#define TFT_DC        10 // Data/command pin
#define TFT_CS        11 // Chip-select pin
#define TFT_RST       24 // Reset pin
#define TFT_RD         9 // Read-strobe pin
#define TFT_BACKLIGHT 25

// Speaker
#define SPEAKER_PIN 14
#define SPEAKER_EN_PIN 50