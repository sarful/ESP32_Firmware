#include <Arduino.h>
#include "WiFiOTA.h"

WiFiOTA ota;  // Everything inside library

#define LED_PIN 2  // Onboard LED pin for most ESP32 boards

void setup() {
  Serial.begin(115200);
  ota.begin();   // Wi-Fi connect + setup
  
  pinMode(LED_PIN, OUTPUT);  // Set onboard LED pin as output
}

void loop() {
  ota.handle();  // Handle OTA update

  // Blink the onboard LED
  digitalWrite(LED_PIN, HIGH);   // Turn the LED on
  
}
