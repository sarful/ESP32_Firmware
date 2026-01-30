#include <Arduino.h>
#include "WiFiOTA.h"

WiFiOTA ota;  // Everything inside library

void setup() {
  Serial.begin(115200);
  ota.begin();   // Wi-Fi connect + setup
}

void loop() {
  ota.handle();  // LED blink + OTA
}
