/*
 *  Sonoff: POW - WiFi Smart Switch with power monitor, Using Homie over MQTT (ESP8266)
 *  Features:
 *    * Mains 10A Relay
 *    * Relay can be toggeled with the onboard pushbutton and external pushbutton
 *    * Green LED indicates Homie status, Red indicates Relay state
 *  Requirements:
 *    * POW Lib for HLW8012 : https://platformio.org/lib/show/1281/HLW8012, PIO: https://platformio.org/lib/show/1281/HLW8012
 */

#include <Homie.h>
#include <SwitchNode.hpp>
#include <HLW8012.h>

#define RELAY_PIN 12
#define LED_PIN 15
#define LED_ACTIVE_STATE HIGH

#define HLW8012_SELECT_PIN 5
#define HLW8012_V_A_PIN 13
#define HLW8012_POW_PIN 14

HLW8012 hlw8012;

bool relayState = false;
SwitchNode relayNode("relay");

void setRelayState(const bool val, const bool overwriteSetter = false) {
  relayState = val;
  digitalWrite(RELAY_PIN, relayState);
  relayNode.setState(relayState, overwriteSetter);
  Homie.getLogger() << "Switch is " << (relayState ? "on" : "off") << endl;
}

void ICACHE_RAM_ATTR hlw8012_p_interrupt() { hlw8012.cf_interrupt(); }
void ICACHE_RAM_ATTR hlw8012_v_a_interrupt() { hlw8012.cf1_interrupt(); }

void setupPowerMonitoring() {
  hlw8012.begin(HLW8012_POW_PIN, HLW8012_V_A_PIN, HLW8012_SELECT_PIN, HIGH, true);
  // hlw8012.setResistors(CURRENT_RESISTOR, VOLTAGE_RESISTOR_UPSTREAM, VOLTAGE_RESISTOR_DOWNSTREAM);

  attachInterrupt(HLW8012_POW_PIN, hlw8012_p_interrupt, CHANGE);
  attachInterrupt(HLW8012_V_A_PIN, hlw8012_v_a_interrupt, CHANGE);
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
