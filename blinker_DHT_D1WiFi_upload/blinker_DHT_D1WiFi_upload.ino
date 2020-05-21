#define BLINKER_WIFI

#include <Blinker.h>

char auth[] = "b55d0d769d02";//秘钥
char ssid[] = "CU_A2eT";//WiFi名称
char pswd[] = "1028507471";//WiFi密码

BlinkerNumber HUMI("humi");//定义键名，与APP中的数据键名一致
BlinkerNumber TEMP("temp");

#include <DHT.h>

#define DHTPIN 4//定义传感器数据引脚

//选择相应的传感器类型
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

uint32_t read_time = 0;

float humi_read, temp_read;

//数据读取函数
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);

    Blinker.vibrate();
    
    uint32_t BlinkerTime = millis();
    
    Blinker.print("millis", BlinkerTime);
}

//数据上传函数
void heartbeat()
{
    HUMI.print(humi_read);
    TEMP.print(temp_read);
}

//数据储存函数
void dataStorage()
{
    //以下内容可以以图表形式显示
    Blinker.dataStorage("temp1", temp_read);
    Blinker.dataStorage("humi1", humi_read);
}

void setup()
{
    Serial.begin(115200);
    BLINKER_DEBUG.stream(Serial);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    Blinker.begin(auth, ssid, pswd);//连接blinker
    Blinker.attachData(dataRead);//获取数据
    Blinker.attachHeartbeat(heartbeat);//数据上传
    Blinker.attachDataStorage(dataStorage);//数据储存
    dht.begin();//传感器初始化
}

void loop()
{
    Blinker.run();

    if (read_time == 0 || (millis() - read_time) >= 2000)
    {
        read_time = millis();

        float h = dht.readHumidity();//读取湿度数值
        float t = dht.readTemperature();//读取温度数值

        //获取失败的提示
        if (isnan(h) || isnan(t)) {
            BLINKER_LOG("Failed to read from DHT sensor!");
            return;
        }
        
        humi_read = h;
        temp_read = t;

        //打印输出
        BLINKER_LOG("Humidity: ", h, " %");
        BLINKER_LOG("Temperature: ", t, " *C");
    }
}
