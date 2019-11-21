# IFTTT

## 概要

m5stickcのボタンを押すとIFTTTのWebhookにjsonを送信します．イベントの発火と同時に文字列を3つまで送信できます．

WiFi環境・IFTTT側でのWebhookの設定が必要です．  
[IFTTT Webhook の参考](https://ifttt.com/maker_webhooks)

## 使い方

動作環境に合わせて[mydefs.h](mydefs.h)内に次の情報を入力してください．

* WIFI_SSID
  * WiFiは2.4GHz帯にしか対応していません．自宅のWiFiを使うときなどは注意してください．
* WIFI_PASS
* IFTTT_WEBHOOK_KEY
  * IFTTTにログインしていれば[このページ](https://ifttt.com/maker_webhooks)のdocumentationから見れます．