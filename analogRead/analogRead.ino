void setup()
{
  // 初始化串口
  Serial.begin(9600);
}
void loop() 
{
// 读出当前光线强度，并输出到串口显示
  int sensorValue = analogRead(A4);
  Serial.println(sensorValue);
  delay(1000);
}
