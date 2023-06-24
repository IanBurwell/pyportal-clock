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

