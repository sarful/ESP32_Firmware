#ifndef WIFI_OTA_H
#define WIFI_OTA_H

#include <Arduino.h>

class WiFiOTA {
public:
    WiFiOTA();        // constructor
    void begin();
    void handle();

private:
    const char* otaURL;
    unsigned long lastCheck;
    void otaUpdate();
};

#endif
