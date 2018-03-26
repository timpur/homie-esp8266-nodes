#pragma once

#include <Homie.h>
#include "Constants.hpp"

class SensorNode : protected HomieNode
{
public:
  SensorNode(const char* id);
  void setValue(const String& value);
private:
  void onReadyToOperate();
};

SensorNode::SensorNode(const char* id): HomieNode(id, TYPE_SENSOR)
{
  advertise(PROP_VALUE);
  advertise(PROP_UNIT);
}

void SensorNode::onReadyToOperate(){
  setProperty(PROP_UNIT).send("unit");
}

void SensorNode::setValue(const String& value){
  setProperty(PROP_VALUE).send(value);
}
