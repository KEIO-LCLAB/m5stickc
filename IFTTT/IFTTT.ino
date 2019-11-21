#include <Arduino.h>
#include <M5StickC.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "mydefs.h"

void postIfttt(String eventName, String* values, int valueNum) {
  
  // eventName: the name of the event you have set in IFTTT
  // values   : an array of String values that you POST to IFTTT
  // valueNum : the number of String values that you want to POST
  //            format of payload varies depending on this number.
  
  const char* CAcert = IFTTT_ROOT_CA;
  String url = "https://maker.ifttt.com/trigger/" + eventName + "/with/key/" + IFTTT_WEBHOOK_KEY;
  String payload = "";
  if (valueNum == 1) {
    payload += "{\"value1\":\"" + values[0] + "\"}";
  } else if (valueNum == 2) {
    payload += "{\"value1\":\"" + values[0] + "\",\"value2\":\"" + values[1] + "\"}";
  } else if (valueNum == 3) {
    payload += "{\"value1\":\"" + values[0] + "\",\"value2\":\"" + values[1] + "\",\"value3\":\"" + values[2] + "\"}";
  }

  HTTPClient https;
  https.begin(url, CAcert);
  https.addHeader("Content-Type", "application/json");
  https.POST(payload);
  https.end();
}

void setup() {
  // initialize pre-installed modules
  M5.begin();

  // rotate display
  M5.Lcd.setRotation(1);

  // connect to access point
  M5.Lcd.print("Connecting to WiFi");

  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }

  M5.Lcd.println();
  M5.Lcd.println("connected");
  M5.Lcd.print("IP address: ");
  M5.Lcd.println(WiFi.localIP());
}

void loop() {
  // update button state
  M5.update();

  // button A for posting to ifttt
  if (M5.BtnA.wasPressed()) {
    // set cursor position at the begining
    M5.Lcd.setCursor(0, 0);

    // erase everything on the display
    M5.Lcd.fillScreen(BLACK);

    // post up to three String values to ifttt via webhook
    M5.Lcd.println("post to ifttt");
    String values[] = {"hoge", "huga", "piyo"};
    postIfttt("test", values, 3);
  }

  // stop executing program to avoid chattering
  delay(100);
}
