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
//----------------------------------------------------------
const char HexLookup[17] = "0123456789ABCDEF";
//----------------------------------------------------------
void setupNetwork() {
  WiFi.begin(ssid, password);
  uint8_t i = 0;
  while (WiFi.status() != WL_CONNECTED && i++ < 20) delay(500);
  if (i == 21) {
    while (1) delay(500);
  }

}
//----------------------------------------------------------







void setup() {
  Serial.begin(115200);
  dht.begin();                            // Khởi tạo DHT1 11 để truyền nhận dữ liệu
  Serial.println("Connecting");

  setupNetwork();

  webSocket.connect(server, port);

  webSocket.emit("event", "led-room");
  //------------------------------------------
}

void loop() {
  webSocket.monitor();
  JSONVar ob;
  if (!webSocket.connected()) {
    webSocket.reconnect(server, port);
  } else {
    Serial.println(server);
  }
  ob["temp"] = dht.readTemperature();
  ob["humi"] = dht.readHumidity();
  Serial.println(ob);
  Serial.println(JSON.stringify(ob));
  webSocket.emit("temperature", JSON.stringify(ob));
  String str = JSON.stringify(ob);
  String input = "{\"result\":true,\"count\":42,\"foo\":\"bar\"}";
  delay(1500);
  webSocket.emit("plainString", input);
  // webSocket.emit("temperature", JSON.stringify(ob));
  delay(1500);
}
