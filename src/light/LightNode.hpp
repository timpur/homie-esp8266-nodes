#pragma once

#include <functional>
#include <Homie.h>
#include "Constants.hpp"
#include "SwitchNode.hpp"

class LightNode : public SwitchNode {
public:
  LightNode(const char* id);
  void setBrightnessCallback(const IntCallback& cb);
  void setBrightnessValue(const int value, const bool overwriteSetter = false);

private:
  IntCallback brightnessCB;
};

LightNode::LightNode(const char* id) : SwitchNode(id, TYPE_LIGHT) {
  advertise(PROP_BRIGHTNESS).settable([this](const HomieRange& range, const String& value) {
    int val = value.toInt();
    if (brightnessCB) brightnessCB(val);
    return true;
  });
}

void LightNode::setBrightnessCallback(const IntCallback& _cb) { brightnessCB = _cb; }

void LightNode::setBrightnessValue(const int value, const bool overwriteSetter) {
  setProperty(PROP_BRIGHTNESS).overwriteSetter(overwriteSetter).send(String(value));
}
