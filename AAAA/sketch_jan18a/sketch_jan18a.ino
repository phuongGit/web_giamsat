
#include <DHT.h>            // Khai báo sử dụng thư viện DHT
#include <ESP8266WiFi.h>    // Khai báo sử dụng thư viện ESP8266WiFi.h để thiết lập chế độ HTTP client cho ESP8266
#include <Arduino_JSON.h>
#include <SocketIOClient.h>

#define LedPin LED_BUILTIN
#define ButtonPin 0

#define DHTPIN D4            // Chân dữ liệu của DHT11 kết nối với GPIO4 của ESP8266
#define DHTTYPE DHT11

// #define SOFTAP_MODE
DHT dht(DHTPIN, DHTTYPE);
const char* ssid = "BANDOTT83";      // Tên mạng Wifi được chỉ định sẽ kết nối (SSID)
const char* password = "20180720";  // Password của mạng Wifi được chỉ định sẽ kết nối

const char* server = "192.168.100.18";     // Địa chỉ IP của máy khi truy cập cùng mạng WiFi
const int port = 8000;                    // Port của server đã mở
const int sendingInternval = 1000;    // Biến cập nhật dữ liệu sau mỗi 2s

SocketIOClient socket;


void setup() {

  Serial.begin(115200);
  dht.begin();                            // Khởi tạo DHT 11 để truyền nhận dữ liệu
  Serial.println("Connecting");

  // Thiết lập ESP8266 là Station và kết nối đến Wifi. in ra dấu `.` trên terminal nếu chưa được kết nối
  WiFi.begin(ssid, password);
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 20) delay(500);
  if (i == 21) {
    while (1) delay(500);
  }
  Serial.println("\r\nWiFi connected");

  socket.connect(server, port);
}

//
// This code runs over and over again
//



void loop() {
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();
  if (socket.connect(server, port)) {
    socket.emit("eventeee", String(temp));
    //---------------------------------------------------------------------------------------

    //---------------------------------------------------------------------------------------
    // terminal trên Arduino.
    Serial.printf("Nhiet do %s - Do am %s\r\n", String(temp, 1).c_str(), String(humi, 1).c_str());
    delay(sendingInternval);
  }
}
