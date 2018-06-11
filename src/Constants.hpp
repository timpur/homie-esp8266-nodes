#pragma once

#include <functional>

// Types
const char TYPE_SENSOR[]    = "sensor";
const char TYPE_SWITCH[]    = "switch";
const char TYPE_LIGHT[]     = "light";
const char TYPE_LIGHT_RGB[] = "light_rgb";

// Properties
const char PROP_VALUE[]      = "value";
const char PROP_ON[]         = "on";
const char PROP_BRIGHTNESS[] = "brightness";
const char PROP_VOLTAGE[]    = "voltage";
const char PROP_CURRENT[]    = "current";
const char PROP_POWER[]      = "power";

// Property Attribute
const char PROP_VALUE_UNIT[] = "_unit";

// Values
const char STATE_ON[]   = "true";
const char STATE_OFF[]  = "false";
const char NULL_VALUE[] = "";

// Units
const char UNIT_VOLTAGE[]     = "V";
const char UNIT_CURRENT[]     = "A";
const char UNIT_POWER[]       = "W";
const char UNIT_FREQUENCY[]   = "Hz";
const char UNIT_TEMPERATURE[] = "°C";
const char UNIT_PERCENT[]     = "%";
const char UNIT_PRESSURE[]    = "Pa";

// Type Def
typedef std::function<void(const bool setValue)> BoolCallback;
typedef std::function<void(const int setValue)> IntCallback;
