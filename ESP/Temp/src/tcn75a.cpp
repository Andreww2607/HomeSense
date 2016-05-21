#include <Arduino.h>
#include "include.h"

const char *decMap[] =
{
	"0", "0625", "125", "1875",
	"25", "3125", "375", "4375",
	"5", "5625", "625", "6875",
	"75", "8125", "875", "9375"
};

void tcnInit() {
	twi_init(I2C_SDA, I2C_SCL);
  twi_setClock(I2C_FRQ);

  unsigned char config[2] = { 0x01, 0x60 }; //config register - 12bit resolution
  unsigned char temp = 0; //select temp register for reading it
  twi_writeTo(I2C_ADDR, config, 2, true);
  twi_writeTo(I2C_ADDR, &temp, 1, true);
}

void tcnReadTemp(char *str) {
  uint8_t buf[2];
  twi_readFrom(I2C_ADDR, buf, 2, true);

	uint8_t msb = buf[0];
	uint8_t lsb = buf[1];

  char *w = str;
	if (msb & 0x80) {*w++='-';msb&=0x7F;}

	uint8_t aux = msb / 100;
	bool st = false;
	if (aux) {*w++=aux+'0';st=true;}

	msb %= 100;
	aux = msb / 10;
	if (aux||st) *w++=aux+'0';

	msb %= 10;
	*w++ = msb+'0';
	*w++ = '.';
	strcpy(w, decMap[lsb >> 4]);
}
