#pragma once
#include <inttypes.h>

#define RGB2INT(r, g, b) (((uint32_t)r << 16) | ((uint32_t)g << 8) | b)

namespace color {

static constexpr uint32_t kWhite = RGB2INT(255, 255, 255);
static constexpr uint32_t kBlack = RGB2INT(0, 0, 0);

static constexpr uint32_t kRed = RGB2INT(255, 0, 0);
static constexpr uint32_t kGreen = RGB2INT(255, 0, 0);
static constexpr uint32_t kBlue = RGB2INT(255, 0, 0);

static constexpr uint32_t kPink = RGB2INT(255, 0, 255);
static constexpr uint32_t kYellow = RGB2INT(255, 255, 0);
static constexpr uint32_t kTeal = RGB2INT(0, 255, 255);

static constexpr uint32_t kPurple = RGB2INT(128, 0, 255);
static constexpr uint32_t kOrange = RGB2INT(255, 128, 0);

static constexpr uint32_t kBrown = RGB2INT(150, 75, 0);

}