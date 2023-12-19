// WS2812_Lib_for_Air001.h
/**
 * Brief	A library for controlling ws2812 in air001 platform.
 * Author	ZhentaoLin
 * Company	None
 * Date		2023-12-18
 * led_pin  PA7
 * Note: 1, The spi function cannot be used when the ws2812 starts.
 * Note: 2, Set the clock source and frequency to 16Mhz.（HSI: 16Mhz, HCLK:16Mhz）
 */
#include "WS2812_Lib_for_Air001.h"

#define LEDS_COUNT  64

AIR001_WS2812 strip = AIR001_WS2812(LEDS_COUNT, TYPE_GRB);

u8 m_color[5][3] = { {255, 0, 0}, {0, 255, 0}, {0, 0, 255}, {255, 255, 255}, {0, 0, 0} };
int delayval = 10;

void setup() {
	strip.begin();
	strip.setBrightness(10);	
}
void loop() {
	for (int j = 0; j < 5; j++) {
		for (int i = 0; i < LEDS_COUNT; i++) {
			strip.setLedColorData(i, m_color[j][0], m_color[j][1], m_color[j][2]);
			strip.show();
			delay(delayval);
		}
		delay(500);
	}
}