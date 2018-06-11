/*
 *   Tested with "WiFi Smart Socket ESP8266 MQTT"
 *   and "Sonoff - WiFi Wireless Smart Switch ESP8266 MQTT"
 *
 *   The Relay could be toggeled with the physical pushbutton
*/

#include <Homie.h>
#include <SwitchNode.hpp>

#define RELAY_PIN 12
#define LED_PIN 13
#define LED_ACTIVE_STATE LOW
#define EXT_BUTTON_PIN 14
#define EXT_BUTTON_ACTIVE_STATE HIGH

bool relayState = false;

OneButton externalButton(EXT_BUTTON_PIN, !EXT_BUTTON_ACTIVE_STATE);
SwitchNode relayNode("relay");

void setRelayState(const bool val,  const bool overwriteSetter = false) {
  relayState = val;
  digitalWrite(RELAY_PIN, relayState);
  digitalWrite(LED_PIN, relayState ? LED_ACTIVE_STATE: !LED_ACTIVE_STATE);
  relayNode.setState(relayState, overwriteSetter);
  Homie.getLogger() << "Switch is " << (relayState ? "on" : "off") << endl;
}

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  pinMode(RELAY_PIN, OUTPUT);
  setRelayState(LOW);

  Homie_setFirmware("itead-sonoff-buton", "1.0.0");
  Homie.setLedPin(LED_PIN, LED_ACTIVE_STATE);

  // Reg Events
  relayNode.setStateCallback([](const bool val) {
    setRelayState(val);
  });
  Homie.setHomieButtonClick([]() {
    setRelayState(!relayState, true);
  });
  externalButton.attachClick([]() {
    setRelayState(!relayState, true);
  });

  Homie.setup();
}

void loop() {
  Homie.loop();
  externalButton.tick();
}
