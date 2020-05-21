#include <Arduino.h>
#include <U8g2lib.h>

#include <DHT.h>

#define DHTPIN 8

#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// 定义OLED 屏幕引脚
//SPI总线：
//U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R2, /* clock=*/ 4, /* data=*/ 5, 
//                                            /* cs=*/ 3, /* dc=*/ 7, /* reset=*/ 6);
//IIC总线
#define SCL 4
#define SDA 5
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R2, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);   // All Boards without Reset of the Display


#define SUN_CLOUD  1

//绘制天气图标
void drawWeatherSymbol(u8g2_uint_t x, u8g2_uint_t y, uint8_t symbol)
{ 
  switch(symbol)
  {
    case SUN_CLOUD:
      u8g2.setFont(u8g2_font_open_iconic_weather_6x_t);
      u8g2.drawGlyph(x, y, 65); 
      break;      
  }
}

//绘制天气图标和温度
void drawWeather(uint8_t symbol, int t,int h )
{
  //绘制天气符号
  drawWeatherSymbol(0,48 , symbol);
  //绘制温度
  u8g2.setFont(/*u8g2_font_logisoso16_tf*/ u8g2_font_lubI12_te );

  u8g2.setCursor(58, 23);
  u8g2.print("T : ");
  u8g2.print(t);
  u8g2.drawGlyph( 109, 21, 176);
  u8g2.setCursor(116, 23);
  u8g2.print("C");
  
  
  u8g2.setCursor(58, 44);
  u8g2.print("H : ");
  u8g2.print(h);
  u8g2.print(" %");   // requires enableUTF8Print()
}

/*
  Draw a string with specified pixel offset. 
  The offset can be negative.
  Limitation: The monochrome font with 8 pixel per glyph
*/

//绘制滚动字幕
void drawScrollString(int16_t offset, const char *s)
{
  static char buf[36];  // should for screen with up to 256 pixel width 
  size_t len;
  size_t char_offset = 0;
  u8g2_uint_t dx = 0;
  size_t visible = 0;
  

  u8g2.setDrawColor(0);   // clear the scrolling area
  u8g2.drawBox(0, 49, u8g2.getDisplayWidth()-1, u8g2.getDisplayHeight()-1);
  u8g2.setDrawColor(1);   // set the color for the text
    
  
  len = strlen(s);
  if ( offset < 0 )
  {
    char_offset = (-offset)/8;
    dx = offset + char_offset*8;
    if ( char_offset >= u8g2.getDisplayWidth()/8 )
      return;
    visible = u8g2.getDisplayWidth()/8-char_offset+1;
    strncpy(buf, s, visible);
    buf[visible] = '\0';
    u8g2.setFont(u8g2_font_8x13_mf);
    u8g2.drawStr(char_offset*8-dx, 62, buf);
  }
  else
  {
    char_offset = offset / 8;
    if ( char_offset >= len )
      return; // nothing visible
    dx = offset - char_offset*8;
    visible = len - char_offset;
    if ( visible > u8g2.getDisplayWidth()/8+1 )
      visible = u8g2.getDisplayWidth()/8+1;
    strncpy(buf, s+char_offset, visible);
    buf[visible] = '\0';
    u8g2.setFont(u8g2_font_8x13_mf);
    u8g2.drawStr(-dx, 62, buf);
  }
  
}

//绘制显示界面
void draw(const char *s, uint8_t symbol, int t,int h)
{
  int16_t offset = -(int16_t)u8g2.getDisplayWidth();
  int16_t len = strlen(s);
  
  u8g2.clearBuffer();         // clear the internal memory
  drawWeather(symbol, t, h);    // draw the icon and degree only once
  for(;;)             // then do the scrolling
  {
  
    drawScrollString(offset, s);        // no clearBuffer required, screen will be partially cleared here
    u8g2.sendBuffer();        // transfer internal memory to the display

    delay(500);
    offset+=2;
    if ( offset > len*8+1 )
      break;
  }
}


void setup(void) {
  Serial.begin(9600);
  dht.begin();
  u8g2.begin();  //初始化OLED
  u8g2.enableUTF8Print();//打开UTF8输出
}

void loop(void) {
    int h = dht.readHumidity();
    int t = dht.readTemperature();
    draw("What a beautiful day!", SUN_CLOUD, t, h);//调用函数绘制显示界面
}
