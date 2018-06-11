/*
 *  Sonoff: Basic - WiFi Smart Switch, Using Homie over MQTT (ESP8266)
 *  Features:
 *    * Mains 10A Relay
 *    * Relay can be toggeled with the onboard pushbutton and external pushbutton
 *    * Green LED indicates Homie status, Red indicates Relay state
 */

#include <Homie.h>
#include <SwitchNode.hpp>
#include <OneButton.h>

#define RELAY_PIN 12
#define LED_PIN 13
#define EXT_BUTTON_PIN 14
#define LED_ACTIVE_STATE LOW
#define EXT_BUTTON_ACTIVE_STATE HIGH

OneButton externalButton(EXT_BUTTON_PIN, !EXT_BUTTON_ACTIVE_STATE);

bool relayState = false;
SwitchNode relayNode("relay");

void setRelayState(const bool val, const bool overwriteSetter = false) {
  relayState = val;
  digitalWrite(RELAY_PIN, relayState);
  digitalWrite(LED_PIN, relayState ? LED_ACTIVE_STATE : !LED_ACTIVE_STATE);
  relayNode.setState(relayState, overwriteSetter);
  Homie.getLogger() << "Switch is " << (relayState ? "on" : "off") << endl;
}

void setup() {
  Serial.begin(115200);
  Homie.getLogger() << endl;

  pinMode(RELAY_PIN, OUTPUT);
  setRelayState(LOW);

  Homie_setFirmware("itead-sonoff-basic-btn", "1.0.0");
  Homie.setLedPin(LED_PIN, LED_ACTIVE_STATE);

  // Reg Events
  relayNode.setStateCallback([](const bool val) { setRelayState(val); });
  Homie.setHomieButtonClick([]() { setRelayState(!relayState, true); });
  externalButton.attachClick([]() { setRelayState(!relayState, true); });

  Homie.setup();
}

void loop() {
  Homie.loop();
  externalButton.tick();
}
