#include <Arduino.h>
#include "ESP8266WiFi.h"
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <IRremoteESP8266.h>
#include "include.h"

WiFiClient wifi;
Adafruit_MQTT_Client mqtt(&wifi, MQTT_SERVER, MQTT_PORT, MQTT_USER, MQTT_PASS);

Adafruit_MQTT_Subscribe lampCommandSubscribe = Adafruit_MQTT_Subscribe(&mqtt, "devices/lamp");

IRrecv irrecv(IR_RCV_PIN);
IRsend irsend(IR_SND_PIN);

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  Serial.println("setup done");

  irrecv.enableIRIn();
  irsend.begin();
  digitalWrite(IR_SND_PIN, LOW);

  mqtt.subscribe(&lampCommandSubscribe);
}

void loop() {
  mqttConnect();

  static decode_results results;

  if (irrecv.decode(&results)) {
    irrecv.resume();
  }

  Adafruit_MQTT_Subscribe *subscription;
  while (subscription = mqtt.readSubscription(1000)) {
    if (subscription == &lampCommandSubscribe) {
      irsend.sendRaw(lampCommandSubscribe.lastread, sizeof(lampCommandSubscribe.datalen), 38);
    }
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
