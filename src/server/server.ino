// server
#include <BLEDevice.h>
#include <BLEUtils.h>

#include <BLEServer.h>

void setup() {
  Serial.begin(115200);
  BLEDevice::init("RSSI-Server"); // Client가 인식할 이름

  // BLE 광고 객체 생성
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x06);  // 기본 설정
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("BLE Server advertising started.");
}

void loop() {
  delay(1000);  // 서버는 반복적으로 광고만 하면 됨
}
