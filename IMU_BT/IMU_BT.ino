#include <BluetoothSerial.h>
#include <M5StickC.h>

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

BluetoothSerial SerialBT;

void setup() {
    M5.begin();
    M5.IMU.Init();
    M5.Lcd.setRotation(3);
    M5.Lcd.fillScreen(BLACK);
    M5.Lcd.setTextSize(1);
    M5.Lcd.setCursor(35, 0);
    M5.Lcd.print("M5StickC_BT_IMU");

    SerialBT.begin("M5StickC");
}

void loop() {
    M5.update();
    if (M5.BtnA.wasPressed()) LCDShow = !LCDShow;

    M5.IMU.getAccelData(&accX, &accY, &accZ);
    M5.IMU.getGyroData(&gyroX, &gyroY, &gyroZ);
    M5.IMU.getAhrsData(&pitch, &roll, &yaw);

    SerialBT.printf("%lu, ", millis());
    SerialBT.printf("%5.2f, %5.2f, %5.2f, ", accX, accY, accZ);
    SerialBT.printf("%6.2f, %6.2f, %6.2f, ", gyroX, gyroY, gyroZ);
    SerialBT.printf("%5.2f, %5.2f, %5.2f\n", pitch, roll, yaw);

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

    // delay(1000);
}
