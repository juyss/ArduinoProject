# https://gitee.com/shmebluk/ArduinoDemoTest.git

### 此仓库用于存放编译通过的arduino项目代码。（位于Arduino项目文件夹内）

#### 程序相关说明

------

Adafruit_SSD1306_Test.ino

Adafruit_SSD1306库的示例文件

------

aida64reader.ino

从上位机读取数据显示在OLED 屏幕上。需要开启AIDA64内存共享和上位机支持

视频地址：

https://www.bilibili.com/video/BV18J411h7zp

------

Colorful-WS2812.ino

FastLED库的示例文件，只需要定义几个简单的参数，便可以很方便的控制你的ws2812灯带

------

D-A-ReadPrint.ino

简单的打印输出数字接口或者模拟接口的值。

------

DHT_D1WiFi_upload.ino

D1 WiFi 模块的示例程序，读取DTH11传感器的温度和湿度，并上传到Blinker，可以通过App看到数据，同时显示为数值和图表，通过*heartbeat()*函数上传数值通过*dataStorage()*函数保存数据以便用图表显示。

------

DS18B20serialprint.ino

串口打印输出DS18b20的温度值。

------

GraphicsTest.ino

使用U8g2库点亮OLED 屏幕，设置屏幕参数，我的为6pin、分辨率128*64、spi协议的，选用以下代码定义：

```c++
U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R0, /* clock=*/ 4, /* data=*/ 5, /* cs=*/ 3, /* dc=*/ 6, /* reset=*/ 7);
```

这是一个图形测试程序。

------

HC-SR05.ino

红外人体感应模块示例代码（没有光敏电阻控制）

------

HC-SR05_with_LDR.ino

红外人体感应模块示例代码（有光敏电阻控制）

-------

OLED_Weather_Display.ino

OLED 屏幕示例程序，具体效果如下图：

[效果图片](https://i0.hdslb.com/bfs/album/0619b843db226a45015acfd64069e6fd81e52372.jpg@518w_1e_1c.jpg)

显示天气图标，温度数值，还有一串滚动字幕。个人感觉很满意的一个项目，当然，升级空间还很大。

------

OLED_and_DS18b20.ino

这个是简单的在OLED 屏幕上显示DS18b20读取到的温度数值，英文显示。

------

analogRead.ino

模拟口数值输出程序

------

dht11.ino

串口发送DHT11传感器的温湿度读数

------

Blynk_DHT11.ino

使用 Arduino UNO 和 W5100以太网扩展板 和 DHT11温湿度传感器 , 
上传温度到Blynk服务器，通过App端实时查看
参考文章：https://www.jianshu.com/p/540347299a37，有很详细的App设置

------

