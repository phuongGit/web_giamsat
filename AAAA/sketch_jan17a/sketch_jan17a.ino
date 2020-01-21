#include <Arduino.h>
#include <DHT.h>
#include <ESP8266WiFi.h>

#include <SocketIOClient.h>

#define USE_SERIAL Serial

SocketIOClient webSocket;

#define DHTPIN D4            // Chân dữ liệu của DHT11 kết nối với GPIO4 của ESP8266
#define DHTTYPE DHT11

// #define SOFTAP_MODE
DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "BANDOTT83";      // Tên mạng Wifi được chỉ định sẽ kết nối (SSID)
const char* password = "20180720";  // Password của mạng Wifi được chỉ định sẽ kết nối

const char* server = "192.168.100.18";     // Địa chỉ IP của máy khi truy cập cùng mạng WiFi
const int port = 8000;                    // Port của server đã mở
const int sendingInternval = 1000;    // Biến cập nhật dữ liệu sau mỗi 2s





void setup() {
  Serial.begin(115200);
  dht.begin();                            // Khởi tạo DHT 11 để truyền nhận dữ liệu
  Serial.println("Connecting");

  // Thiết lập ESP8266 là Station và kết nối đến Wifi. in ra dấu `.` trên terminal nếu chưa được kết nối
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("\r\nWiFi connected");

  webSocket.emit("event", "esp 8266 send");
  webSocket.connect(server, port);
}

void loop() {
  webSocket.monitor();
}
