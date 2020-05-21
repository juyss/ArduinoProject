//人体感应模块实例代码;
int ledPin = 13;
int pirPin = 3;

int pirValue;
int sec = 0;

void setup()
{
  pinMode(ledPin, OUTPUT);
  pinMode(pirPin, INPUT);

  digitalWrite(ledPin, LOW);
  Serial.begin(9600);
}

void loop()
{
    pirValue = digitalRead(pirPin);
    digitalWrite(ledPin, pirValue);
  

  // 以下注释可以观察传感器输出状态
  delay(1000);
}
