#pragma once

#include <functional>

// Types
const char TYPE_SENSOR[] = "sensor";
const char TYPE_SWITCH[] = "switch";
const char TYPE_LIGHT[] = "light";
const char TYPE_LIGHT_RGB[] = "light_rgb";

// Props
const char PROP_VALUE[] = "value";
const char PROP_UNIT[] = "unit";
const char PROP_ON[] = "on";
const char PROP_BRIGHTNESS[] = "brightness";

// Values
const char STATE_ON[] = "true";
const char STATE_OFF[] = "false";

// Type Def
typedef std::function<void(const bool setValue)> BoolCallback;
typedef std::function<void(const int setValue)> IntCallback;
