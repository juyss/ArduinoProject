#include <dht.h>
dht DHT;
#define DHT11_PIN 8//put the sensor in the digital pin 8

#include <LiquidCrystal_I2C.h>
#include <Wire.h> 
#include <stdio.h>
#include <string.h>
#include <DS1302.h>
LiquidCrystal_I2C lcd(0x27,20,4);// set the LCD address to 0x27 for a 16 chars and 2 line display

uint8_t CE_PIN   = 5;//接口定义 CE(DS1302 pin5) -> Arduino D5
uint8_t IO_PIN   = 6;// IO(DS1302 pin6) -> Arduino D6
uint8_t SCLK_PIN = 7;//SCLK(DS1302 pin7) -> Arduino D7

char buf[50];//* 日期变量缓存 */
char day[10];
DS1302 rtc(CE_PIN, IO_PIN, SCLK_PIN);/* 创建 DS1302 对象 */
Time t;
void setup()
{
  Serial.begin(9600);
  rtc.write_protect(false);
  rtc.halt(false);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(1,0);

}

void loop()
{
  Time t = rtc.time();
  memset(day, 0, sizeof(day));
  switch (t.day)
  {
  case 1: 
    strcpy(day, "Sun"); 
    break;
  case 2: 
    strcpy(day, "Mon"); 
    break;
  case 3: 
    strcpy(day, "Tue"); 
    break;
  case 4: 
    strcpy(day, "Wed"); 
    break;
  case 5: 
    strcpy(day, "Thu"); 
    break;
  case 6: 
    strcpy(day, "Fri"); 
    break;
  case 7: 
    strcpy(day, "Sat"); 
    break;
  }
  snprintf(buf, sizeof(buf), "%s %04d-%02d-%02d ", day, t.yr, t.mon, t.date);
  lcd.setCursor(1,0); 
  lcd.print(buf); 
  //lcd.setCursor(10, 1);
  //lcd.print("Beyond"); 
  snprintf(buf, sizeof(buf), "%02d:%02d:%02d", t.hr, t.min, t.sec);
  lcd.setCursor(1, 1);
  lcd.print(buf);

  // READ DATA
  Serial.print("DHT11, \t");
 int chk = DHT.read11(DHT11_PIN);
  switch (chk)
  {
    case 0:  Serial.print("OK,\t"); break;
    case -1: Serial.print("Checksum error,\t"); break;
    case -2: Serial.print("Time out error,\t"); break;
    default: Serial.print("Unknown error,\t"); break;
  }
 // DISPLAT DATA
  Serial.print(DHT.humidity,1);
  Serial.print(",\t");
  Serial.println(DHT.temperature,1);
  lcd.setCursor(10, 1);
  int hum=DHT.humidity;
  lcd.print(hum);
  lcd.setCursor(13, 1);
  int tem=DHT.temperature;
  lcd.print(tem);  
  

  delay(1000);                    
}
