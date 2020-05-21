#include <dht11.h>

dht11 DHT11;

#define DHT11PIN 2 //定义引脚 DHT11 dataPin => arduino D2

void setup()
{
  Serial.begin(9600);
  Serial.println("DHT11 TEST PROGRAM ");
  Serial.print("LIBRARY VERSION: ");
  Serial.println(DHT11LIB_VERSION);
  Serial.println();
}

void loop()
{
  Serial.println("\n");

  int chk = DHT11.read(DHT11PIN);

  Serial.print("Read sensor: ");
  switch (chk)
  {
    case DHTLIB_OK: 
                Serial.println("OK"); 
                break;
    case DHTLIB_ERROR_CHECKSUM: 
                Serial.println("Checksum error"); 
                break;
    case DHTLIB_ERROR_TIMEOUT: 
                Serial.println("Time out error"); 
                break;
    default: 
                Serial.println("Unknown error"); 
                break;
  }

  Serial.print("Humidity (%): 湿度");
  Serial.println((float)DHT11.humidity, 2);//获取湿度数值

  Serial.print("Temperature (oC): 温度");
  Serial.println((float)DHT11.temperature, 2);//获取温度数值

  delay(2000);
}
