#include <Arduino.h>
#include "ESP8266WiFi.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include "include.h"

WiFiClient wifi;
Adafruit_MQTT_Client mqtt(&wifi, MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_PASS);

const char GAS_TOPIC[] = "sensors/gas";
Adafruit_MQTT_Publish gasPublish = Adafruit_MQTT_Publish(&mqtt, GAS_TOPIC);

const char PRESENCE_TOPIC[] = "sensors/presence";
Adafruit_MQTT_Publish presencePublish = Adafruit_MQTT_Publish(&mqtt, PRESENCE_TOPIC);

void setup() {
  Serial.begin(115200);

  pinMode(GAS_PIN, INPUT_PULLUP);
  pinMode(PIN_PPRES, INPUT);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.println("setup done");
}

void loop() {
  mqttConnect();

  static unsigned long timer = 0;
  unsigned long now = millis();
  if (now > 10000 && now > timer) { //10sec warm-up time
    timer = now + 500;

    static int lastState = 0xFF;
    int state = digitalRead(GAS_PIN);
    if (state != lastState) {
      lastState = state;
      gasPublish.publish(state ? 0 : 1);
    }

    static int lastPir = 0xFF;
    state = digitalRead(PIN_PPRES);
    if (state != lastPir) {
      lastPir = state;
      presencePublish.publish(state ? 1 : 0);
    }
  }
}

void mqttConnect() {
  if (mqtt.connected()) return;

  Serial.print("connecting to MQTT...");

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
