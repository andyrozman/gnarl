#include <pins_arduino.h>
#include "gnarl_config.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wignored-qualifiers"
#include <SSD1306.h>
#pragma GCC diagnostic pop

extern "C" {
#include "oled.h"
}


#define LEDPIN 2
#define OLED_I2C_ADDR 0x3C
#define OLED_RESET 16

#ifdef GNARL_DEVICE_TTGO_V1

	#define XOLED_SDA 4
	#define XOLED_SCL 15

#endif

#ifdef GNARL_DEVICE_TTGO_V2

	#define XOLED_SDA 21
	#define XOLED_SCL 22

#endif

static SSD1306 d(OLED_I2C_ADDR, XOLED_SDA, XOLED_SCL);

void oled_init() {

	pinMode(OLED_RESET , OUTPUT);
  	pinMode(LEDPIN,OUTPUT); // might be unneeded ??

  	digitalWrite(OLED_RESET, LOW);    // set GPIO16 low to reset OLED
  	delay(50);
  	digitalWrite(OLED_RESET, HIGH); // while OLED is running, must set GPIO16 in high

	d.init();
	d.flipScreenVertically();
}

void oled_on() {
	d.displayOn();
}

void oled_off() {
	d.displayOff();
}

void oled_clear() {
	// d.clear() leaves artifacts
	d.resetDisplay();
}

void oled_update() {
	d.display();
}

void font_small() {
	d.setFont(ArialMT_Plain_10);
}

void font_medium() {
	d.setFont(ArialMT_Plain_16);
}

void font_large() {
	d.setFont(ArialMT_Plain_24);
}

void align_left() {
	d.setTextAlignment(TEXT_ALIGN_LEFT);
}

void align_right() {
	d.setTextAlignment(TEXT_ALIGN_RIGHT);
}

void align_center() {
	d.setTextAlignment(TEXT_ALIGN_CENTER);
}

void align_center_both() {
	d.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
}

void draw_string(int x, int y, const char *s) {
	d.drawString(x, y, s);
}
