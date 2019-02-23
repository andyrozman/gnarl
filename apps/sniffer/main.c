#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

#include <esp_task_wdt.h>

#include "rfm95.h"
#include "config.h"
#include "oled.h"

#define TIMEOUT 60*1000	// 1 minute, in milliseconds

uint8_t rx_buf[256];
char str[100];


void display_info(int read_rssi, int count) {
	oled_clear();
	font_medium();
	align_center_both();
	draw_string(0, 0, "Sniffer");
	font_small();
	align_left();
	sprintf(str, "Count:  %d", count);
	draw_string(0, 21, str);
    sprintf(str, "RSSI: %d", read_rssi);
	draw_string(0, 42, str);
	oled_update();
	//printf("Entry...%d\n", count);
}

void splash() {
	oled_init();
    font_large();
    align_center_both();
    draw_string(64, 32, "Sniffer");
    oled_update();
}


void app_main() {

	rfm95_init();
	uint8_t v = read_version();
	printf("radio version %d.%d\n", version_major(v), version_minor(v));
	set_frequency(PUMP_FREQUENCY);
	printf("frequency set to %d Hz\n", read_frequency());
	splash();
	for (;;) {
		esp_task_wdt_reset();
		int n = sleep_receive(rx_buf, sizeof(rx_buf), TIMEOUT);
		if (n == 0) {
			printf("[timeout]\n");
			continue;
		}
		for (int i = 0; i < n; i++) {
			printf("%02X ", rx_buf[i]);
		}

		int rssi = read_rssi();
		int count = rx_packet_count();

		printf("(RSSI = %d, # bytes = %d, count = %d)\n", rssi, n, count);
		display_info(rssi, count);
	}
}
