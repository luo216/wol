#define BLINKER_PRINT Serial
#define BLINKER_WIFI

#include <Blinker.h>
#include <WiFiUdp.h>
#include <WakeOnLan.h>

WiFiUDP UDP;
WakeOnLan WOL(UDP); // Pass WiFiUDP class

char auth[] = "点灯给你密钥";
char ssid[] = "WIFI名称";
char pswd[] = "WIFI密码";
const char *MACAddress = "需要被激活设备的MAC地址";

// 新建组件对象
BlinkerButton Button1("btn-abc");

void wakeMyPC() {
    WOL.sendMagicPacket(MACAddress); // 发送 Wake On Lan 魔法包到指定的 MAC 地址。
}

// 按下按键即会执行该函数
void button1_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    // 发送WakeOnLan魔法包
    wakeMyPC();
    // 闪烁LED 3次
    for (int i = 0; i < 3; i++) {
        digitalWrite(LED_BUILTIN, LOW); // 打开LED
        delay(500); // 等待500ms
        digitalWrite(LED_BUILTIN, HIGH); // 关闭LED
        delay(500); // 等待500ms
    }

}

// 如果未绑定的组件被触发，则会执行其中内容
void dataRead(const String & data)
{
    BLINKER_LOG("Blinker readString: ", data);
}

void setup() {
    // 初始化串口
    Serial.begin(115200);

    #if defined(BLINKER_PRINT)
        BLINKER_DEBUG.stream(BLINKER_PRINT);
    #endif
    
    // 初始化内置LED的IO
    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH); // 默认LED为关闭状态

    // 初始化blinker
    Blinker.begin(auth, ssid, pswd);
    Blinker.attachData(dataRead);
    Button1.attach(button1_callback);

    WOL.setRepeat(3, 100); // Repeat the packet three times with 100ms delay between
}

void loop() {
    Blinker.run();
}
