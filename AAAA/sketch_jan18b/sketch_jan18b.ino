#include <ESP8266WiFi.h>
#include <SocketIOClient.h>

SocketIOClient client;
const char* ssid = "BANDOTT83";      // Tên mạng Wifi được chỉ định sẽ kết nối (SSID)
const char* password = "20180720";  // Password của mạng Wifi được chỉ định sẽ kết nối

const char* host = "192.168.100.18";     // Địa chỉ IP của máy khi truy cập cùng mạng WiFi
const int port = 3000;                  //Cổng dịch vụ socket server do chúng ta tạo!


extern String RID;
extern String Rfull;

unsigned long previousMillis = 0;
long interval = 2000;

void setup()
{
  ​Serial.begin(115200);
  ​delay(10);

  ​Serial.print("Ket noi vao mang ")
  ​Serial.println(ssid);

  ​//Kết nối vào mạng Wif
  ​WiFi.begin(ssid, password);

  ​while (WiFi.status() != WL_CONNECTED) { //Thoát ra khỏi vòng
    ​delay(500);
    ​Serial.print('.');
    ​

    ​Serial.println();
    ​Serial.println(F("Da ket noi WiFi"));
    ​Serial.println(F("Di chi IP cua ESP8266 (Socket Client ESP8266): "));
    ​Serial.println(WiFi.localIP());

    ​if (!client.connect(host, port))
      ​Serial.println(F("Ket noi den socket server that bai!"));
      ​return;
        ​

        ​//Khi đã kết nối thành côn
        ​if (client.connected())
          ​//Thì gửi sự kiện ("connection") đến Socket server ahihi
          ​client.send("connection", "message", "Connected !!!!");
          ​
      }

  void loop()
  {
    ​//tạo một task cứ sau "interval" giây thì chạy lệnh
    ​if (millis() - previousMillis > interval)
      ​//lệnh
      ​previousMillis = millis() {

      ​//gửi sự kiện "atime" là một JSON chứa tham số message có nội dung là Time please
      ​client.send("atime", "message", "Time please?");
      ​

      ​//Khi bắt được bất kỳ sự kiện nào thì chúng ta có hai tham số
      ​//  +RID: Tên sự kiệ
      ​//  +RFull: Danh sách tham số được nén thành chuỗi JSON
      ​if (client.monitor()) {
        ​Serial.println(RID);
        ​Serial.println(Rfull);
        ​

        ​//Kết nối lại
        ​if (!client.connected()) {
          ​client.reconnect(host, port);          ​
        }
      }
    }
  }
