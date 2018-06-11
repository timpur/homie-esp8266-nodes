#pragma once

#include <Homie.h>
#include "Constants.hpp"

class SensorNode : public HomieNode {
public:
  SensorNode(const char* id, const char* unit);
  void setValue(const String& value);

private:
  const char* _unit;
  void onReadyToOperate();
};

SensorNode::SensorNode(const char* id, const char* unit) : HomieNode(id, TYPE_SENSOR), _unit(unit) {
  advertise(PROP_VALUE);
  advertise(PROP_VALUE_UNIT);
}

void SensorNode::onReadyToOperate() { setProperty(PROP_VALUE_UNIT).send(_unit); }

void SensorNode::setValue(const String& value) { setProperty(PROP_VALUE).send(value); }
