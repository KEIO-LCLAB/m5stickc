# BT_IMU

## 概要

M5StickCで測定した加速度，角速度，姿勢方位を Bluetooth Serial 経由でパソコンに送り，CSVファイルとして書き出すためのプログラムのセットです．

## 使い方

Arduino スケッチをM5StickCに書き込んだ上でパソコンとのペアリングが必要です．

* M5StickCをBluetoothでペアリングする方法
  * 通常のBluetoothデバイスとは異なるため注意
  * Windowsの設定→デバイス→Bluetoothとその他のデバイス→デバイスとプリンターを選択(別ウィンドウが開かれる)
  * デバイスの追加からM5StickCを選択(Arduinoのプログラム上SerialBT.begin()で設定した名前が表示される)
* ペアリングするとCOMポートが複数つくられる問題
  * Windowsの設定→デバイス→Bluetoothとその他のデバイス→その他のBluetoothオプションを選択
  * 「COMポート」タブでポート一覧を表示
  * 名前に「ESP32SPP」が含まれているポートが通信できる
    * SPP: Serial Port Profile

Python プログラムは実行時に保存するCSVファイル名を自分で決めることができます．

一度の記録の実行につきM5StickCの再起動をしないとうまく記録が行われない問題があります．原因は今のところ判っていません．