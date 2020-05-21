const int buttonPin = 2; // 连接按键的引脚
const int ledPin = 13;   // 连接LED的引脚

int buttonState = 0;

void setup()
{
  // 初始化LED引脚为输出状态
  pinMode(ledPin, OUTPUT);
  // 初始化按键引脚为输入状态
  pinMode(buttonPin, INPUT);
  // 初始化串口
  Serial.begin(9600);
}
void loop()
{
  // 读取按键状态并存储在变量中
  buttonState = digitalRead(buttonPin);

  // 检查按键是否被按下
  // 如果按键按下，那buttonState应该为高电平
  if (buttonState == HIGH)
  {
    // 点亮LED
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    // 熄灭LED
    digitalWrite(ledPin, LOW);
  }
  // 读出当前光线强度，并输出到串口显示
  int sensorValue = analogRead(A0);
  Serial.println(sensorValue);
  Serial.println(buttonPin);
  delay(1000);
}
