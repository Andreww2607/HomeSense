#include <Arduino.h>
#include "ESP8266WiFi.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "include.h"

WiFiClient wifi;
Adafruit_MQTT_Client mqtt(&wifi, MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_PASS);

Adafruit_MQTT_Subscribe outletRelay1Subscribe = Adafruit_MQTT_Subscribe(&mqtt, "devices/outlet/1");
Adafruit_MQTT_Subscribe outletRelay2Subscribe = Adafruit_MQTT_Subscribe(&mqtt, "devices/outlet/2");

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.println("setup done");

  pinMode(PIN_RELAY1, OUTPUT);
  pinMode(PIN_RELAY2, OUTPUT);
  digitalWrite(PIN_RELAY1, LOW);
  digitalWrite(PIN_RELAY2, LOW);

  mqtt.subscribe(&outletRelay1Subscribe);
  mqtt.subscribe(&outletRelay2Subscribe);
}

void loop() {
  mqttConnect();

  Adafruit_MQTT_Subscribe *subscription;
  while (subscription = mqtt.readSubscription(1000)) {
    if (subscription == &outletRelay1Subscribe)
      digitalWrite(PIN_RELAY1, strcmp((char*)outletRelay1Subscribe.lastread, "on") == 0 ? HIGH : LOW);
    else if (subscription == &outletRelay2Subscribe)
      digitalWrite(PIN_RELAY2, strcmp((char*)outletRelay2Subscribe.lastread, "on") == 0 ? HIGH : LOW);
  }
}

void mqttConnect() {
  if (mqtt.connected()) return;

  Serial.println("connecting to MQTT...");

  uint8_t retries = 5;
  int8_t ret;
  while ((ret = mqtt.connect()) != 0) {
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("retrying MQTT in 5 sec");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0)
         ESP.reset();
  }

  Serial.println("mqtt connected!");
}
