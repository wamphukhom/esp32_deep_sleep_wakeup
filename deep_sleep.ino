
#include <SPI.h>
#include <WiFi.h>

#include "esp_sleep.h"

#define INTERVAL_MESSAGE1 5000 //5วินาที
#define INTERVAL_MESSAGE2 7000 //7วินาที
#define INTERVAL_MESSAGE3 11000 //11วินาที
#define INTERVAL_MESSAGE4 13000 //13วินาที

#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  20        /* Time ESP32 will go to sleep (in seconds) */

const char *ssid     = "ADMIN";
const char *password = "12345678";

int t = 0;
unsigned long time_1 = 0;
unsigned long time_2 = 0;
unsigned long time_3 = 0;
unsigned long time_4 = 0;
 
void print_time(unsigned long time_millis);

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  String ppoint = ".";
//  while (WiFi.status() != WL_CONNECTED)
  for (int i=0; i<= 5; i++) {
    if(WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println(String(ppoint));
      delay(1000);
      ppoint += String("K");
    }
    else {
      Serial.println(String(WiFi.localIP()));
      delay(3000);
      break;
    }
  }
}
 
void setup() {
  Serial.begin(115200);
  initWiFi();
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR); // หลังจาก esp_deep_sleep_start แล้วนับไปอีก 20วิจะเริ่มทำงาน
}
 
void loop() {
    if(millis() - time_1 > INTERVAL_MESSAGE1){
        time_1 = millis();
        print_time(time_1);
        Serial.println("I'm message number one!");
    }
   
    if(millis() - time_2 > INTERVAL_MESSAGE2){
        time_2 = millis();
        print_time(time_2);
        Serial.println("Hello, I'm the second message.");
        esp_deep_sleep_start();
    }
   
    if(millis() - time_3 > INTERVAL_MESSAGE3){
        time_3 = millis();
        print_time(time_3);
        Serial.println("My name is Message the third.");
    }
   
    if(millis() - time_4 > INTERVAL_MESSAGE4){
        time_4 = millis();
        print_time(time_4);
        Serial.println("Message four is in the house!");
    }
}
 
void print_time(unsigned long time_millis){
    Serial.print("Time: ");
    Serial.print(time_millis/1000);
    Serial.print("s - ");
}
