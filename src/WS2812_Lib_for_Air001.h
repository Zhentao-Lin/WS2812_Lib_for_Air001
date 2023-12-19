// WS2812_Lib_for_Air001.h
/**
 * Brief	A library for controlling ws2812 in air001 platform.
 * Author	ZhentaoLin
 * Company	None
 * Date		2023-12-18
 */

 #ifndef _WS2812_LIB_FOR_AIR_H
#define _WS2812_LIB_FOR_AIR_H

#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include "WProgram.h"
#endif

#include<SPI.h>

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;

#define NR_OF_LEDS   256  //最大支持420多个，但是定义越大消耗空间越多。自行把握。

enum LED_TYPE
{					  //R  G  B
	TYPE_RGB = 0x06,  //00 01 10
	TYPE_RBG = 0x09,  //00 10 01
	TYPE_GRB = 0x12,  //01 00 10
	TYPE_GBR = 0x21,  //10 00 01
	TYPE_BRG = 0x18,  //01 10 00
	TYPE_BGR = 0x24	  //10 01 00
};

class AIR001_WS2812
{
protected:
	u16 ledCounts;               //用来记录用户申请的彩灯的数目
    u8 br;                       //用来记录彩灯的亮度值
	u8 rOffset;                  //用来记录彩灯红色部分的数据
	u8 gOffset;                  //用来记录彩灯红色部分的数据
	u8 bOffset;                  //用来记录彩灯红色部分的数据
	u32 led_data[NR_OF_LEDS];    //申请最多256个彩灯的数据空间


public:
	AIR001_WS2812(u16 n = 8, LED_TYPE t = TYPE_GRB);

	void begin();                                               //初始化彩灯配置（注意，使用内部16Mhz时钟, SPI的MOSI引脚（A7）需要2分频）
	void setLedCount(u16 n);                                    //设置彩灯的数目
	void setLedType(LED_TYPE t);                                //设置灯珠类型
	void setBrightness(u8 brightness);                          //设置彩灯亮度

  bool set_pixel(int index, u8 r, u8 g, u8 b);

	bool setLedColorData(int index, u32 rgb);                   //设置指定的ws2812的颜色，设置但不生效，仅是修改了数组中的颜色数据
	bool setLedColorData(int index, u8 r, u8 g, u8 b);          //设置指定的ws2812的颜色，设置但不生效，仅是修改了数组中的颜色数据

	bool setLedColor(int index, u32 rgb);                       //设置指定的ws2812的颜色，设置后就生效
	bool setLedColor(int index, u8 r, u8 g, u8 b);              //设置指定的ws2812的颜色，设置后就生效

	bool setAllLedsColorData(u32 rgb);                          //设置全部彩灯的颜色，设置但不生效，仅是修改了数组中的颜色数据
	bool setAllLedsColorData(u8 r, u8 g, u8 b);                 //设置全部彩灯的颜色，设置但不生效，仅是修改了数组中的颜色数据

	bool setAllLedsColor(u32 rgb);                              //设置全部彩灯的颜色，设置后就生效
	bool setAllLedsColor(u8 r, u8 g, u8 b);                     //设置全部彩灯的颜色，设置后就生效
  
	bool show();                                                //生效数组中的彩灯颜色数据

	uint32_t Wheel(u8 pos);                                     //色盘取色。形参范围0-255，返回形参对应色盘的颜色值
	uint32_t hsv2rgb(uint32_t h, uint32_t s, uint32_t v);       //hsv转rgb
};

#endif

