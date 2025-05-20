// server
#include <BLEDevice.h>
#include <BLEUtils.h>

#include <BLEServer.h>

void setup() {
  Serial.begin(115200);
  BLEDevice::init("RSSI-Server"); // name

  // create BLE advertising instance
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->setScanResponse(false);
  pAdvertising->setMinPreferred(0x06);  // default setting
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  Serial.println("BLE Server advertising started.");
}

void loop() {
  delay(1000);  // idle
}
