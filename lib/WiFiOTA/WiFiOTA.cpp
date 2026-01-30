#include "WiFiOTA.h"
#include <WiFi.h>
#include <WiFiManager.h>
#include <HTTPClient.h>
#include <Update.h>

// Default OTA firmware URL
static const char* DEFAULT_OTA_URL = 
"https://raw.githubusercontent.com/sarful/ESP32_Firmware/main/.pio/build/esp32dev/firmware.bin";

WiFiOTA::WiFiOTA() {
    otaURL = DEFAULT_OTA_URL;
    lastCheck = 0;
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
    // Check OTA every 30 sec
    if (millis() - lastCheck < 30000) return;
    lastCheck = millis();

    otaUpdate();
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
                ESP.restart();
            }
        }
    }

    http.end();
}
