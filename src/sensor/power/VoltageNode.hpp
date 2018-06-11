#pragma once

#include "Constants.hpp"
#include "../SensorNode.hpp"

class VoltageNode : public SensorNode {
public:
  VoltageNode(const char* id);
  void setVoltage(const float value);
};

VoltageNode::VoltageNode(const char* id) : SensorNode(id, UNIT_VOLTAGE, PROP_VOLTAGE) {}

void VoltageNode::setVoltage(const float value) { setValue(String(value)); }
