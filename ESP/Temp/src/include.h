#include "../../config.h"

#define I2C_ADDR 0x48
#define I2C_SDA 14
#define I2C_SCL 12
#define I2C_FRQ 100000

#define LED_PIN 13

void mqttConnect();
void tcnInit();
void tcnReadTemp(char *str);
