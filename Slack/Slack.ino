#include <Arduino.h>
#include <M5StickC.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "mydefs.h"

void postSlack(String message) {

  // message: the String value that you want to POST
  
  const char* CAcert = SLACK_ROOT_CA;
  String url = SLACK_WEBHOOK_URL;
  String payload = "{\"text\":\"" + message + "\"}";

  HTTPClient https;
  https.begin(url, CAcert);
  https.addHeader("Content-Type", "application/json");
  https.POST(payload);
  https.end();
}

void setup() {
  // initialize modules
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

  // button A for posting to slack
  if (M5.BtnA.wasPressed()) {
    // set cursor position at the begining
    M5.Lcd.setCursor(0,0);
    
    // erase everything on the display
    M5.Lcd.fillScreen(BLACK);
    
    // post massage to slack via webhook
    M5.Lcd.println("post to slack");
    postSlack("Your message goes here.");
  }

  // stop executing program to avoid chattering
  delay(100);
}
