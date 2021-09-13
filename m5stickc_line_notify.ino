#include <ssl_client.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include "M5StickC.h"
#include "M5Display.h"

const char* ssid = "WIFI_SSID";
const char* password = "WIFI_PASS";

void wifiConnect() {
  WiFi.disconnect();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);  // Wi-Fi接続
  while (WiFi.status() != WL_CONNECTED) {  // Wi-Fi 接続待ち
    delay(100);
    Serial.printf(".");
  }
  Serial.println("\nwifi connect ok");
}
void send(String message) {
  const char* host = "notify-api.line.me";
  const char* token = "YOURE_TOKEN";
  WiFiClientSecure client;
  Serial.println("Try");
  client.setInsecure();
  //LineのAPIサーバに接続
  if (!client.connect(host, 443)) {
    Serial.println("Connection failed");
    return;
  }
  Serial.println("Connected");
  //リクエストを送信
  String query = String("message=") + message;
  String request = String("") +
               "POST /api/notify HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Authorization: Bearer " + token + "\r\n" +
               "Content-Length: " + String(query.length()) +  "\r\n" + 
               "Content-Type: application/x-www-form-urlencoded\r\n\r\n" +
                query + "\r\n";
  client.print(request);

  //受信終了まで待つ 
  while (client.connected()) {
    String line = client.readStringUntil('\n');
    Serial.println(line);
    if (line == "\r") {
      break;
    }
  }

  String line = client.readStringUntil('\n');
  Serial.println(line);
}

void setup() {
  M5.begin();
  M5.Axp.ScreenBreath(9);
  setCpuFrequencyMhz(80);
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLUE);
  wifiConnect();
  M5.Lcd.setTextSize(2);
  M5.Lcd.setCursor(0,40);
  M5.Lcd.println("STANDBY OK !");
}

void loop() {
  M5.update();
  M5.Lcd.setCursor(0,40);
  if (M5.BtnA.wasPressed()){ //ボタンA(真ん中の大きいボタン）
    send("ボタンを押したよ～");
    M5.Lcd.fillScreen(GREEN);
    M5.Lcd.println("AISATSU SEND !");
    delay(5000);
    M5.Lcd.setCursor(0,40);
    M5.Lcd.fillScreen(BLUE);
    M5.Lcd.println("STANDBY OK !");
  }
  if (M5.BtnB.wasPressed()){ //ボタンB(側面のボタン）
    send("緊急事態だよ！");
    M5.Lcd.fillScreen(RED);
    M5.Lcd.println("KINKYU SEND !");
    delay(5000);
    M5.Lcd.setCursor(0,40);
    M5.Lcd.fillScreen(BLUE);
    M5.Lcd.println("STANDBY OK !");
  }

}
