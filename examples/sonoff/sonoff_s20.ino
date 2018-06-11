/*
 *  Sonoff: s20 - WiFi Smart Switch, Using Homie over MQTT (ESP8266)
 *  Features:
 *    * Mains 10A Relay
 *    * Relay can be toggeled with the onboard pushbutton
 *    * Green LED indicates Homie status, Red indicates Relay state
 */

#include <Homie.h>
#include <SwitchNode.hpp>

#define RELAY_PIN 12
#define LED_PIN 13
#define LED_ACTIVE_STATE LOW

bool relayState = false;
SwitchNode relayNode("relay");

void setRelayState(const bool val, const bool overwriteSetter = false) {
  relayState = val;
  digitalWrite(RELAY_PIN, relayState);
  relayNode.setState(relayState, overwriteSetter);
  Homie.getLogger() << "Switch is " << (relayState ? "on" : "off") << endl;
}

void setup() {
  Serial.begin(115200);
  Homie.getLogger() << endl;

  pinMode(RELAY_PIN, OUTPUT);
  setRelayState(LOW);

  Homie_setFirmware("itead-sonoff-s20", "1.0.0");
  Homie.setLedPin(LED_PIN, LED_ACTIVE_STATE);

  // Reg Events
  relayNode.setStateCallback([](const bool val) { setRelayState(val); });
  Homie.setHomieButtonClick([]() { setRelayState(!relayState, true); });

  Homie.setup();
}

void loop() { Homie.loop(); }
