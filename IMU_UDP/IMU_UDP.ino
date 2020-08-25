/*
 *  This sketch sends random data over UDP on a ESP32 device
 *
 */
#include <M5StickC.h>
#include <WiFi.h>
#include <WiFiUdp.h>

// 取得した加速度を格納する変数
float accX = 0.0F;
float accY = 0.0F;
float accZ = 0.0F;

// 取得した角速度を格納する変数
float gyroX = 0.0F;
float gyroY = 0.0F;
float gyroZ = 0.0F;

// 取得した姿勢方位を格納する変数
float pitch = 0.0F;
float roll = 0.0F;
float yaw = 0.0F;

// LCD表示のON/OFF切り替え
bool LCDShow = false;

// WiFi ネットワークの SSID と パスワード:
const char* networkName = "**SSID**";
const char* networkPswd = "**PASSWORD**";

// UDPパケットを送る先のIPアドレス:
// Windows PC のIPアドレスを調べるには Power Shell で ipconfig を実行
const char* udpAddress = "**IP_ADDRESS**";
const int udpPort = 3333;

// WiFiの接続状況
boolean connected = false;

// UDPライブラリのクラス
WiFiUDP udp;

void setup() {
    M5.begin();
    M5.IMU.Init();
    M5.Lcd.setRotation(3);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(35, 0);
    M5.Lcd.print("M5StickC_IMU_UDP");

    // シリアルを初期化(USBのやつ)
    Serial.begin(115200);

    // WiFiネットワークに接続
    connectToWiFi(networkName, networkPswd);
}

void loop() {
    M5.update();
    if (M5.BtnA.wasPressed()) LCDShow = !LCDShow;

    M5.IMU.getAccelData(&accX, &accY, &accZ);
    M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
    M5.IMU.getAhrsData(&pitch, &roll, &yaw);

    // WiFi接続中のときのみデータを送信
    if (connected) {
        // パケットを送信
        udp.beginPacket(udpAddress, udpPort);
        udp.printf("%lu, ", millis());
        udp.printf("%5.2f, %5.2f, %5.2f, ", accX, accY, accZ);
        udp.printf("%6.2f, %6.2f, %6.2f, ", gyroX, gyroY, gyroZ);
        udp.printf("%5.2f, %5.2f, %5.2f\n", pitch, roll, yaw);
        udp.endPacket();
    }

    if (LCDShow) {
        M5.Lcd.setCursor(0, 10);
        M5.Lcd.println("  X       Y       Z");
        M5.Lcd.setCursor(0, 20);
        M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", accX, accY, accZ);
        M5.Lcd.setCursor(140, 20);
        M5.Lcd.print("acc");
        M5.Lcd.setCursor(0, 30);
        M5.Lcd.printf("%6.2f  %6.2f  %6.2f      ", gyroX, gyroY, gyroZ);
        M5.Lcd.setCursor(140, 30);
        M5.Lcd.print("gyr");
        M5.Lcd.setCursor(0, 50);
        M5.Lcd.println("  Pitch   Roll    Yaw");
        M5.Lcd.setCursor(0, 60);
        M5.Lcd.printf(" %5.2f   %5.2f   %5.2f   ", pitch, roll, yaw);
    }

    // 1秒待つ
    // delay(1000);
}

void connectToWiFi(const char* ssid, const char* pwd) {
    Serial.println("Connecting to WiFi network: " + String(ssid));

    // 古い構成を削除
    WiFi.disconnect(true);
    // イベントハンドラを登録
    WiFi.onEvent(WiFiEvent);

    // 接続を開始
    WiFi.begin(ssid, pwd);

    Serial.println("Waiting for WIFI connection...");
}

// WiFiイベントハンドラ
void WiFiEvent(WiFiEvent_t event) {
    switch (event) {
        case SYSTEM_EVENT_STA_GOT_IP:
            // connected がセットされたばあい
            Serial.print("WiFi connected! IP address: ");
            Serial.println(WiFi.localIP());
            // UDP の状態を初期化
            // 送信バッファを初期化する
            udp.begin(WiFi.localIP(), udpPort);
            connected = true;
            break;
        case SYSTEM_EVENT_STA_DISCONNECTED:
            Serial.println("WiFi lost connection");
            connected = false;
            break;
        default:
            break;
    }
}
