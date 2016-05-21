#define WIFI_SSID "YOUR WIFI"
#define WIFI_PASS "YOUR PASS"

#define MQTT_SERVER "192.168.0.2"
#define MQTT_PORT 1883
#define MQTT_USER ""
#define MQTT_PASS ""

#define I2C_ADDR 0x48
#define I2C_SDA 14
#define I2C_SCL 12
#define I2C_FRQ 100000

#define LED_PIN 13

void mqttConnect();
void tcnInit();
void tcnReadTemp(char *str);
