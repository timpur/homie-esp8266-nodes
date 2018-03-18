#pragma once

#include <functional>
#include <Homie.h>

typedef std::function<void(const bool setValue)> SwitchCallback;

const char STATE_PROP[] = "on";
const char STATE_ON_VALUE[] = "true";
const char STATE_OFF_VALUE[] = "false";


class SwitchNode : HomieNode
{
public:
  SwitchNode(const char* id);
  void setCallback(const SwitchCallback& cb);
  void setValue(const bool value, const bool overwriteSetter = false);
private:
  SwitchCallback cb;
};

SwitchNode::SwitchNode(const char* id): HomieNode(id, "switch")
{
  advertise(STATE_PROP).settable([this](const HomieRange& range, const String& value) {
    bool val = (value == STATE_ON_VALUE);
    if(cb) cb(val);
    return true;
  });
}

void SwitchNode::setCallback(const SwitchCallback& _cb){
  cb = _cb;
}

void SwitchNode::setValue(const bool value,  const bool overwriteSetter){
  setProperty(STATE_PROP).overwriteSetter(overwriteSetter).send(value ? STATE_ON_VALUE : STATE_OFF_VALUE);
}
