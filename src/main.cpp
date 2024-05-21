#include <M5StickCPlus.h>
#include "AXP192.h"

void setup() {
  M5.begin();
  M5.IMU.Init();
  Serial.begin(115200);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setRotation(4);
  M5.Lcd.setTextFont(4);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("OMIKUJI");
}

void showFortune() {
  const char* fortunes[] = {
    "Great luck",
    "Good luck",
    "Moderate luck",
    "Small luck",
    "Bad luck",
    "Very bad luck"
  };
  int numFortunes = sizeof(fortunes) / sizeof(fortunes[0]);
  int randomIndex = random(numFortunes);

  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print(fortunes[randomIndex]);
  delay(7000);  // 7秒表示
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.print("OMIKUJI");
}

void loop() {
  float accX = 0, accY = 0, accZ = 0;

  // 加速度を取得
  M5.IMU.getAccelData(&accX, &accY, &accZ);

  // 逆さにされたかどうかをチェック
  if (accZ < -0.7) {  // Z軸の値が-0.8以下なら逆さにされている
    // 振られるのを待つ
    while (true) {
      M5.IMU.getAccelData(&accX, &accY, &accZ);
      if (abs(accX) > 1.5 || abs(accY) > 1.5 || abs(accZ) > 1.5) {
        showFortune();
        break;
      }
      delay(100);
    }
  }
  delay(100);
}
