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
  ota.handle();  // LED blink + OTA

  // Blink the onboard LED
//   digitalWrite(LED_PIN, HIGH);   // Turn the LED on
//   delay(1400);                    // Wait for 500 milliseconds
//   digitalWrite(LED_PIN, LOW);    // Turn the LED off
//   delay(500);                    // Wait for 500 milliseconds
// 
}
