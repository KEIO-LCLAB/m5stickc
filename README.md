# m5stickc

m5stickcのサンプルコード集です．m5stickcの開発環境については[公式のチュートリアル](https://docs.m5stack.com/#/en/quick_start/m5stickc/m5stickc_quick_start_with_arduino_Windows)を参考にしてください．（日本語版のページもありますが，情報が古いです．）ArduinoIDEにライブラリを追加するだけで簡単に開発を始められます．

以下，各サンプルコードの概要を説明します．

## IFTTT

m5stickcのボタンを押すとIFTTTのWebhookにjsonを送信します．イベントの発火と同時に文字列を3つまで送信できます．

WiFi環境・IFTTT側でのWebhookの設定が必要です．  
[IFTTT Webhook の参考](https://ifttt.com/maker_webhooks)

## Slack

m5stickcのボタンを押すとWebhook経由でSlackにメッセージを投稿できます．

WiFi環境・Slack側でのWebhookアプリの設定が必要です．  
[Slack Webhook の参考](https://slack.com/intl/ja-jp/help/articles/115005265063)

## BT_IMU

M5StickCで測定した加速度，角速度，姿勢方位を Bluetooth Serial 経由でパソコンに送り，CSVファイルとして書き出すためのプログラムのセットです．