# WS2812 Lib for Air001

## Description
This is an Arduino library for controlling ws2812b led on Air001.

## Examples:

Here are some simple examples.

### Show Rainbow
This example make your strip show a flowing rainbow.

```
#include <Arduino.h>
#include <EC11_Encoder.h>

#if defined(ARDUINO_AVR_UNO)
const int8_t pinA = 9;
const int8_t pinB = 10;
#if defined(ESP32)
const int8_t pinA = 36;
const int8_t pinB = 39;
#if defined(AIR001xx)
const int8_t pinA = PA_13;
const int8_t pinB = PA_14;
#endif

EC11Encoder encoder(pinA, pinB);

void setup() {
  Serial.begin(115200);
  Serial.println(F("Polling in loop()"));
}

void loop() {
  encoder.service();                          
  int encoder_change = encoder.get_change();  
  if (encoder_change) {
    Serial.println(encoder.get_count());    
  }
}
```

## Usage
```
EC11Encoder encoder(pinA, pinB);
```
* Construction. Create a encoder object.

```
encoder.service();  
```
* Repeat calls to get the state of the encoder.
```
int encoder_change = encoder.get_change();  
```
* Get the status of the encoder. 

```
encoder.get_count()
```
* Get the count from the encoder


