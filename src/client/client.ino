#include <BLEDevice.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#define LED_PIN 5              // D5 = GPIO5
#define UART_TX 17             // connected to Web ESP32 RXD2(GPIO16)
#define UART_RX 16             // Not used

const String targetName = "RSSI-Server";
const int txPower = -59;       // 1m distance's RSSI
const float n = 2.0;           // path-loss exponent

BLEScan* pBLEScan;

class MyAdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks {
  void onResult(BLEAdvertisedDevice advertisedDevice) {
    if (advertisedDevice.getName() == targetName) {
      int rssi = advertisedDevice.getRSSI();
      float distance = pow(10.0, ((float)txPower - rssi) / (10 * n));

      // Serial print (for debug)
      Serial.print("RSSI: ");
      Serial.print(rssi);
      Serial.print(" dBm → Estimated Distance: ");
      Serial.print(distance, 2);
      Serial.println(" m");

      // transmit distance data
      Serial2.println(distance, 2);

      // LED alert
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
  Serial.begin(115200);                         
  Serial2.begin(115200, SERIAL_8N1, UART_RX, UART_TX); // transmit to Web Server board
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  BLEDevice::init("");
  pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
}

void loop() {
  pBLEScan->start(1, false);  // scan for one second
  delay(5000);                // period: 5 seconds
}
