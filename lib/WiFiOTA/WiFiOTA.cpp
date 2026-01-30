#include "WiFiOTA.h"
#include <WiFi.h>
#include <WiFiManager.h>
#include <HTTPClient.h>
#include <Update.h>

#define LED_PIN 2   // Built-in LED pin

// Default OTA firmware URL
static const char* DEFAULT_OTA_URL = 
"https://raw.githubusercontent.com/sarful/ESP32_Firmware/main/.pio/build/esp32dev/firmware.bin";

// Blink settings
static int blinkDelay = 1000; // Default: slow blink

WiFiOTA::WiFiOTA() {
    otaURL = DEFAULT_OTA_URL;
    lastCheck = 0;
    pinMode(LED_PIN, OUTPUT);
}

void WiFiOTA::begin() {
    // WiFiManager auto connect
    WiFiManager wm;
    wm.setConfigPortalTimeout(180);
    if (!wm.autoConnect("ESP32-Setup")) {
        ESP.restart();
    }
    Serial.println("WiFi Connected");
}

void WiFiOTA::handle() {
    // Blink LED
    blinkLED();

    // Check OTA every 30 sec
    if (millis() - lastCheck < 30000) return;
    lastCheck = millis();

    otaUpdate();
}

// Internal LED blink
void WiFiOTA::blinkLED() {
    digitalWrite(LED_PIN, HIGH);
    delay(blinkDelay);
    digitalWrite(LED_PIN, LOW);
    delay(blinkDelay);
}

// Internal OTA check
void WiFiOTA::otaUpdate() {
    if (WiFi.status() != WL_CONNECTED) return;

    HTTPClient http;
    http.begin(otaURL);
    int code = http.GET();

    if (code == HTTP_CODE_OK) {
        int len = http.getSize();
        if (Update.begin(len)) {
            WiFiClient* stream = http.getStreamPtr();
            Update.writeStream(*stream);
            if (Update.end()) {
                Serial.println("OTA Updated → Restarting");
                blinkDelay = 200; // FAST blink after update
                ESP.restart();
            }
        }
    }

    http.end();
}
