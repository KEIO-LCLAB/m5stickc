# Slack

## 概要

m5stickcのボタンを押すとWebhook経由でSlackにメッセージを投稿できます．

WiFi環境・Slack側でのWebhookアプリの設定が必要です．  
[Slack Webhook の参考](https://slack.com/intl/ja-jp/help/articles/115005265063)

## 使い方

動作環境に合わせて[mydefs.h](mydefs.h)内に次の情報を入力してください．

* WIFI_SSID
  * WiFiは2.4GHz帯にしか対応していません．自宅のWiFiを使うときなどは注意してください．
* WIFI_PASS
* SLACK_WEBHOOK_URL
  * [このページ](https://slack.com/intl/ja-jp/help/articles/115005265063)を参考にSlackにWebhookを設定してください．そうすればwebhookのURLが得られます．