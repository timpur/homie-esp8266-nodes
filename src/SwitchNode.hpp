#pragma once

#include <functional>
#include <Homie.h>
#include "Constants.hpp"

class SwitchNode : public HomieNode
{
public:
  SwitchNode(const char *id, const char *type = TYPE_SWITCH);
  void setStateCallback(const BoolCallback &callback);
  void setState(const bool value, const bool overwriteSetter = false);

private:
  BoolCallback stateCallback;
};

SwitchNode::SwitchNode(const char *id, const char *type) : HomieNode(id, type)
{
  advertise(PROP_ON).settable([this](const HomieRange &range, const String &value) {
    bool val = (value == STATE_ON);
    if (stateCallback)
      stateCallback(val);
    return true;
  });
}

void SwitchNode::setStateCallback(const BoolCallback &_callback)
{
  stateCallback = _callback;
}

void SwitchNode::setState(const bool value, const bool overwriteSetter)
{
  setProperty(PROP_ON).overwriteSetter(overwriteSetter).send(value ? STATE_ON : STATE_OFF);
}
