#pragma once

#include <Homie.h>

const char VALUE[] = "value";
const char UNIT[] = "unit";

class SensorNode : HomieNode
{
public:
  SensorNode(const char* id);
  void setValue(const String& value);
private:
  void onReadyToOperate();
};

SensorNode::SensorNode(const char* id): HomieNode(id, "sensor")
{
  advertise(VALUE);
  advertise(UNIT);
}

void SensorNode::onReadyToOperate(){
  setProperty(UNIT).send("unit");
}

void SensorNode::setValue(const String& value){
  setProperty(VALUE).send(value);
}
