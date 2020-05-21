#include <Arduino.h>
#include <U8g2lib.h>

#include <OneWire.h>
#include <DallasTemperature.h>

// DS18b20数据输出脚接开发板数字引脚2
#define ONE_WIRE_BUS 8

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
//定义OLED连接线序
U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 4, /* data=*/ 5, 
                                            /* cs=*/ 3, /* dc=*/ 7, /* reset=*/ 6);

void setup(void) {
  Serial.begin(9600);
  sensors.begin(); //初始化DS18b20
  u8g2.begin();  //初始化OLED
  u8g2.enableUTF8Print();//打开UTF8输出
}

void loop(void) {
//    u8g2.setFont(u8g2_font_ncenB10_tr);//设置字体
    u8g2.setFont(u8g2_font_wqy15_t_chinese1);
    u8g2.setFontDirection(0);
    u8g2.clearBuffer();          // 清除内部缓冲区
    u8g2.setCursor(0, 40);
    u8g2.print("现在是：");
    sensors.requestTemperatures(); // 发送命令获取温度
    float val = sensors.getTempCByIndex(0);//将获取到的温度数值保存在变量中
    u8g2.setCursor(54,40);    //设置光标位置
    u8g2.print(val);  //输出变量数值
    u8g2.setCursor(99, 40);//设置光标位置
    u8g2.println("度"); //单位
    u8g2.sendBuffer(); // 屏幕输出
    delay(100);
}
