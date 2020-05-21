/* 作者：flyAkari 会飞的阿卡林 bilibili UID:751219*/

#include <U8g2lib.h>

//U8G2_SSD1306_128X64_NONAME_F_4W_SW_SPI u8g2(U8G2_R2, /* clock=*/ 4, /* data=*/ 5, /* cs=*/ 3, /* dc=*/ 6, /* reset=*/ 7); //SPI软串口
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R2,/* clock=*/ 5, /* data=*/ 6,  /* reset=*/U8X8_PIN_NONE); //IIC软串口
//U8G2_SSD1306_128X64_NONAME_F_4W_HW_SPI u8g2(U8G2_R0, /* cs=*/ 4, /* dc=*/ 5, /* reset=*/ 3); //使用7个引脚SPI屏幕的取消注释这行并注释掉上一行
char tcpu[25], scpuuti[25], smemuti[25], fcpu[25];//用来存着4个数值
char id[15];
char value[25];
byte inByte;

void refresh()
{
    u8g2.clearBuffer();                         // 清空显存
    u8g2.setFont(u8g2_font_unifont_t_chinese2); // 选一个合适的字体
    u8g2.drawStr(0, 15, "CPU Temp:");
    u8g2.drawStr(73, 15, tcpu); //CPU温度
    u8g2.drawStr(97, 15, "'C");
    u8g2.drawStr(0, 30, "CPU Util:");
    u8g2.drawStr(73, 30, scpuuti); //CPU占用率
    u8g2.drawStr(105, 30, "%");
    u8g2.drawStr(0, 45, "RAM Util:"); 
    u8g2.drawStr(73, 45, smemuti); //内存占用率
    u8g2.drawStr(105, 45, "%");
    u8g2.drawStr(0, 60, "CPU Funs:");
    u8g2.drawStr(73, 60, fcpu); //CPU风扇转速
    u8g2.drawStr(105, 60, "rpm");
    u8g2.sendBuffer(); // 打到屏幕上
}

void setup()
{
    // put your setup code here, to run once:
    u8g2.begin();
    u8g2.enableUTF8Print(); //开启后能显示一些中文字
    Serial.begin(115200);
}

void loop()
{
    if (Serial.available() > 0)
    {   //数据帧格式：?TCPU=37!
        inByte = Serial.read();
        if (inByte == '?')
        {
            int i = 0;
            while (inByte != '=')
            {
                while (Serial.available() == 0)
                    ;
                inByte = Serial.read();
                if (inByte != '=')
                {
                    id[i++] = inByte;
                }
                else
                {
                    id[i] = '\0';
                }
            }
            i = 0;
            while (inByte != '!')
            {
                while (Serial.available() == 0)
                    ;
                inByte = Serial.read();
                if (inByte != '!')
                {
                    value[i++] = inByte;
                }
                else
                {
                    value[i] = '\0';
                }
            }
            i = 0;
            Serial.println(id); //如果需要显示其他的信息，去上位机输出里查名称
            Serial.println(value);
            if (strcmp("TCPU", id) == 0)
                strcpy(tcpu, value);
            if (strcmp("SCPUUTI", id) == 0)
                strcpy(scpuuti, value);
            if (strcmp("SMEMUTI", id) == 0)
                strcpy(smemuti, value);
            if (strcmp("FCPU", id) == 0)
                strcpy(fcpu, value);
            refresh();
        }
    }
}
