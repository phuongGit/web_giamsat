#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <Arduino_JSON.h>
#include <SocketIOClient.h>

#define USE_SERIAL Serial
#include <DHT.h>
#define DHTPIN D4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
WiFiClient client;
const char* ssid = "BANDOTT83";
const char* password = "20180720";
const char* server = "192.168.100.18";
const int port = 8000;
const int sendingInternval = 2 * 1000;



ESP8266WiFiMulti WiFiMulti;
SocketIOClient webSocket;

void event(const char * payload, size_t length) {
  USE_SERIAL.printf("got message: %s\n", payload);
}

void setup() {
  Serial.begin(115200);
  dht.begin();                            // Khởi tạo DHT1 11 để truyền nhận dữ liệu
  Serial.println("Connecting");

  // Thiết lập ESP8266 là Station và kết nối đến Wifi. in ra dấu `.` trên terminal nếu chưa được kết nối
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(100);
  }
  Serial.println("\r\nWiFi connected");
  USE_SERIAL.setDebugOutput(true);

  USE_SERIAL.println();
  USE_SERIAL.println();
  USE_SERIAL.println();

  for (uint8_t t = 4; t > 0; t--) {
    USE_SERIAL.printf("[SETUP] BOOT WAIT %d...\n", t);
    USE_SERIAL.flush();
    delay(1000);
  }
  webSocket.emit("plainString", "this is a plain string");
  webSocket.connect(server, port);
  webSocket.emit("event", "led-room");
  //------------------------------------------
}

void loop() {
  webSocket.monitor();
  if (webSocket.connected()) {
    JSONVar ob;
    char a[] = "aa";
    int b = 3;
    ob["temp"] = dht.readTemperature();
    ob["humi"] = dht.readHumidity();

    Serial.println(ob);

    webSocket.emit("temperature", JSON.stringify(ob));
    Serial.println(ob);
  } else {
    Serial.println(server);
  }
  delay(1500);
}
