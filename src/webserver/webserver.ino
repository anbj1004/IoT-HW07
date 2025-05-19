hw7 webserver


#include <WiFi.h>

// ✅ Wi-Fi 설정
const char* ssid = "AndroidHotspotEB_4A_03";
const char* password = "11113111";

// UART 설정
#define RXD2 16   // BLE Client TX 연결
#define TXD2 17   // 사용 안함

float receivedDistance = 0.0;
WiFiServer server(80);
String header;

void setup() {
  Serial.begin(115200);       // Web ESP32 자체 디버그용
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2); // BLE Client로부터 수신

  // Wi-Fi 연결
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500); Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP address: "); Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  // 🟢 BLE Client로부터 거리값 수신
  if (Serial2.available()) {
    String raw = Serial2.readStringUntil('\n');
    raw.trim();
    float dist = raw.toFloat();
    if (dist > 0.0 && dist < 20.0) {
      receivedDistance = dist;
      Serial.print("Received distance: ");
      Serial.println(receivedDistance, 2);
    }
  }

  // 🌐 웹서버 동작
  WiFiClient client = server.available();
  if (client) {
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println("Connection: close\n");
    client.print("<!DOCTYPE html><html><head><meta http-equiv='refresh' content='3'></head><body>");
    client.print("<h1>BLE Distance Web Monitor</h1><p>Distance: ");
    client.print(receivedDistance, 2);
    client.print(" m</p>");
    if (receivedDistance <= 1.0) {
      client.print("<p style='color:red;'>⚠️ TOO CLOSE!</p>");
    }
    client.print("</body></html>");
    delay(1);
    client.stop();
  }
}
