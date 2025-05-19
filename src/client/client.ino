#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#define LED_PIN 5              // D5 = GPIO5
#define UART_TX 17             // Web ESP32의 RXD2(예: GPIO16)과 연결됨
#define UART_RX 16             // 사용 안함, 설정만 필요

const String targetName = "RSSI-Server";
const int txPower = -59;       // 1m 거리 기준 RSSI
const float n = 2.0;           // 환경 계수

BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    if (advertisedDevice.getName() == targetName) {
      int rssi = advertisedDevice.getRSSI();
      float distance = pow(10.0, ((float)txPower - rssi) / (10 * n));

      // 시리얼 출력 (디버그용)
      Serial.print("RSSI: ");
      Serial.print(rssi);
      Serial.print(" dBm → Estimated Distance: ");
      Serial.print(distance, 2);
      Serial.println(" m");

      // UART2로 Web Server ESP32에 거리값 전송
      Serial2.println(distance, 2);

      // LED 경고
      if (distance <= 1.0) {
        digitalWrite(LED_PIN, HIGH);
        Serial.println("⚠️ WARNING: Distance ≤ 1.0m → LED ON");
      } else {
        digitalWrite(LED_PIN, LOW);
      }

      Serial.println("----------");
    }
  }
};

void setup() {
  Serial.begin(115200);                         // PC로 디버깅
  Serial2.begin(115200, SERIAL_8N1, UART_RX, UART_TX); // Web Server 보드로 송신
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
}

void loop() {
  pBLEScan->start(1, false);  // 1초 스캔
  delay(5000);                // 5초 주기 반복
}
