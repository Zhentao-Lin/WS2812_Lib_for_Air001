// WS2812_Lib_for_Air001.h
/**
 * Brief    A library for controlling ws2812 in air001 platform.
 * Author   ZhentaoLin
 * Company  None
 * Date     2023-12-18
 */

#include "WS2812_Lib_for_Air001.h"

AIR001_WS2812::AIR001_WS2812(u16 n /*= 8*/, LED_TYPE t /*= TYPE_GRB*/)
{
    ledCounts = n;     //记录用户申请的彩灯数目
    br = 255;          //默认最大亮度（0-255）
    setLedType(t);     //设置彩灯的颜色数据类型
}

void AIR001_WS2812::begin()
{   
  SPI.begin();                          //初始化SPI
  SPI.setBitOrder(MSBFIRST);            //高位在前，低位在后
  SPI.setDataMode(SPI_MODE1);           //设置spi为模式1
  SPI.setClockDivider(SPI_CLOCK_DIV2);  //芯片设置16M，SPI配置为2分频，确保为8Mhz
}

void AIR001_WS2812::setLedCount(u16 n)
{
    ledCounts = n;
    begin();
}

void AIR001_WS2812::setLedType(LED_TYPE t)
{
    rOffset = (t >> 4) & 0x03;
    gOffset = (t >> 2) & 0x03;
    bOffset = t & 0x03;
}

void AIR001_WS2812::setBrightness(u8 brightness)
{
    br = constrain(brightness, 0, 255);
}

bool AIR001_WS2812::set_pixel(int index, u8 r, u8 g, u8 b)
{
    u32 color = r << 16 | g << 8 | b ;
  led_data[index] = color;
    return 1;
}


bool AIR001_WS2812::setLedColorData(int index, u32 rgb)
{
    return setLedColorData(index, rgb >> 16, rgb >> 8, rgb);
}

bool AIR001_WS2812::setLedColorData(int index, u8 r, u8 g, u8 b)
{
    u8 p[3];
    p[rOffset] = r * br / 255;
    p[gOffset] = g * br / 255;
    p[bOffset] = b * br / 255;
    return set_pixel(index, p[0], p[1], p[2]);
}

bool AIR001_WS2812::setLedColor(int index, u32 rgb)
{
    return setLedColor(index, rgb >> 16, rgb >> 8, rgb);
}

bool AIR001_WS2812::setLedColor(int index, u8 r, u8 g, u8 b)
{
    setLedColorData(index, r, g, b);
    return show();
}

bool AIR001_WS2812::setAllLedsColorData(u32 rgb)
{
    for (int i = 0; i < ledCounts; i++)
    {
        setLedColorData(i, rgb);
    }
    return 1;
}

bool AIR001_WS2812::setAllLedsColorData(u8 r, u8 g, u8 b)
{
    for (int i = 0; i < ledCounts; i++)
    {
        setLedColorData(i, r, g, b);
    }
    return 1;
}

bool AIR001_WS2812::setAllLedsColor(u32 rgb)
{
    setAllLedsColorData(rgb);
    return show();
}

bool AIR001_WS2812::setAllLedsColor(u8 r, u8 g, u8 b)
{
    setAllLedsColorData(r, g, b);
    return show();
}

bool AIR001_WS2812::show()
{
  u32 value = 0;
  for (int i = 0; i < ledCounts; i++){
    value = led_data[i];
    for(int j = 0; j < 24; j++){
      if ((value & 0x800000) != LOW) {
        SPI.transfer(0xF8);//1
        asm("nop");
        asm("nop");
      } 
      else {
        SPI.transfer(0xC0);//0
      }
      value <<= 1;
    }
  }
  delayMicroseconds(60);
  return 1;
}

uint32_t AIR001_WS2812::Wheel(byte pos)
{
    u32 WheelPos = pos % 0xff;
    if (WheelPos < 85) {
        return ((255 - WheelPos * 3) << 16) | ((WheelPos * 3) << 8);
    }
    if (WheelPos < 170) {
        WheelPos -= 85;
        return (((255 - WheelPos * 3) << 8) | (WheelPos * 3));
    }
    WheelPos -= 170;
    return ((WheelPos * 3) << 16 | (255 - WheelPos * 3));
}

uint32_t AIR001_WS2812::hsv2rgb(uint32_t h, uint32_t s, uint32_t v)
{
    u8 r, g, b;
    h %= 360; // h -> [0,360]
    uint32_t rgb_max = v * 2.55f;
    uint32_t rgb_min = rgb_max * (100 - s) / 100.0f;

    uint32_t i = h / 60;
    uint32_t diff = h % 60;

    // RGB adjustment amount by hue
    uint32_t rgb_adj = (rgb_max - rgb_min) * diff / 60;

    switch (i) {
    case 0:
        r = rgb_max;
        g = rgb_min + rgb_adj;
        b = rgb_min;
        break;
    case 1:
        r = rgb_max - rgb_adj;
        g = rgb_max;
        b = rgb_min;
        break;
    case 2:
        r = rgb_min;
        g = rgb_max;
        b = rgb_min + rgb_adj;
        break;
    case 3:
        r = rgb_min;
        g = rgb_max - rgb_adj;
        b = rgb_max;
        break;
    case 4:
        r = rgb_min + rgb_adj;
        g = rgb_min;
        b = rgb_max;
        break;
    default:
        r = rgb_max;
        g = rgb_min;
        b = rgb_max - rgb_adj;
        break;
    }
    return (uint32_t)(r << 16 | g << 8 | b);
}
