# Freenove WS2812 Lib for Air001

## Description
This is an Arduino library for controlling ws2812b led on Air001.

## Examples:

Here are some simple examples.

### Show Rainbow
This example make your strip show a flowing rainbow.

```
#include "WS2812_Lib_for_Air001.h"

#define LEDS_COUNT  64

AIR001_WS2812 strip = AIR001_WS2812(LEDS_COUNT, TYPE_GRB);

void setup() {
  strip.begin();
  strip.setBrightness(20);  
}

void loop() {
  for (int j = 0; j < 255; j += 2) {
    for (int i = 0; i < LEDS_COUNT; i++) {
      strip.setLedColorData(i, strip.Wheel((i * 256 / LEDS_COUNT + j) & 255));
    }
    strip.show();
    delay(10);
  }  
}

```

## Usage
```
AIR001_WS2812 strip = AIR001_WS2812(LEDS_COUNT, TYPE_GRB);
```
* Construction. Create a strip object.

```
strip.begin()
```
Initialization data, ready for communication.
```
strip.setLedColorData(id, color);
strip.setLedColorData(id, r, g, b);
```
* Send the color data of the specified LED to the controller. 
* Display color change after calling show function.
	* id: the index of led.
	* color: color value. egg, 0xFF0000 is RED color.
	* r,g,b: color value. 0-255.
```
strip.show();
```
* Immediately display the color data that has been sent.


```
strip.setLedColor(id, color);
strip.setLedColor(id, r, g, b);
```
* Send color data and display it immediately.
* It is equivalent to "strip.setLedColorData(id, color); strip.show();"
	* id: the index of led.
	* color: color value. egg, 0xFF0000 is RED color.
	* r,g,b: color value. 0-255.

```
strip.Wheel(i)
```
* A simple color picker.
	* i: 0-255.
<img src='extras/ColorWheel.jpg' width='100%'/>

