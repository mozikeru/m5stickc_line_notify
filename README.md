# m5stickc_line_notify

## これは何
M5StickCのボタン押下で、あらかじめ設定しておいたLINEグループにメッセージを飛ばす

## 設定
・コード中の下記の該当箇所にそれぞれ環境情報を入力してからM5StickCに書き込み

【WiFi接続情報】  
const char* ssid = "WIFI_SSID";  
const char* password = "WIFI_PASS";

【LINE Notifyのトークン】  
const char* token = "YOURE_TOKEN";

※LINE Notifyのトークン取得はこちらから  
https://notify-bot.line.me/my/