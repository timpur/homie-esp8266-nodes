#pragma once

#include <functional>
#include <Homie.h>

typedef std::function<void(const bool setValue)> SwitchCallback;

const char VALUE[] = "value";
const char VALUE_ON_STATE[] = "true";
const char VALUE_OFF_STATE[] = "false";


class SwitchNode : HomieNode
{
public:
  SwitchNode(const char* id);
  void setCallback(SwitchCallback& cb);
  void setValue(const bool value, const bool overwriteSetter = false);
private:
  SwitchCallback cb;
};

SwitchNode::SwitchNode(const char* id): HomieNode(id, "switch")
{
  advertise(VALUE).settable([this](const HomieRange& range, const String& value) {
    bool val = (value == VALUE_ON_STATE);
    if(cb) cb(val)
    return true;
  });
}

void SwitchNode::setCallback(SwitchCallback& _cb){
  cb = _cb;
}

void SwitchNode::setValue(const bool value,  const bool overwriteSetter){
  setProperty(VALUE).overwriteSetter(overwriteSetter).send(value ? VALUE_ON_STATE : VALUE_OFF_STATE);
}
