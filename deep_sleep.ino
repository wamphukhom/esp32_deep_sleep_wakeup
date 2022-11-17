 #include <NTPClient.h>
 #include <WiFi.h>
 #include <WiFiUdp.h>
 #include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

char ssid[] = "ADMIN_2g";       // your network SSID (name)
char password[] = "4635410009";  // your network key

// กำหนดค่า offset time เนื่องจากเวลาของเซิฟเวอร์นี้เป็นเวลา UTC เราต้องทำให้เป็นเวลาของประเทศไทย
// เวลาของประเทศไทย = UTC+7 ชั่วโมง ต้องกำหนด offset time = 7 ชั่วโมง
const long offsetTime = 25200;       // หน่วยเป็นวินาที จะได้ 7*60*60 = 25200

// กำหนด object ของ WiFiUDP ชื่อว่า ntpUDP
WiFiUDP ntpUDP;

// กำหนด object ของ NTPClient ชื่อว่า timeClient มีรูปแบบ ("WiFiUDP Object","NTP Server Address","offset time")
NTPClient timeClient(ntpUDP, "pool.ntp.org", offsetTime);

// กำหนดตัวแปรเก็บค่าเวลา ชั่วโมง-นาที-วินาที
int hourNow, minuteNow, secondNow;

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  String ppoint = ".";
//  while (WiFi.status() != WL_CONNECTED)
  for (int i=0; i<= 10; i++) {
    if(WiFi.status() != WL_CONNECTED) {
      delay(1000);
      showlcd("Connecting", String(ppoint));
      delay(1000);
      showlcd("Connecting", String(ppoint));
      delay(1000);
      ppoint += String(".");
    }
    else {
      showlcd(String(WiFi.localIP()), "RSSI : " + String(WiFi.RSSI()));
      delay(3000);
      showlcd("    WELLCOME    ", "INTERNET IN TIME");
      break;
    }
  }
}

void showlcd(String line1, String line2) {
  lcd.setCursor(0, 0);
  lcd.print(line1);
  lcd.setCursor(0, 1);
  lcd.print(line2);
}

void setup(){
// เริ่มใช้งาน LCD
  lcd.begin();
  lcd.backlight();
  WiFi.begin(ssid, password);
// เริ่มการทำงานของ NTPClient
  timeClient.begin();
  initWiFi();
  lcd.clear();
}

void loop() {

  if (WiFi.status() == WL_NO_SHIELD) {
    initWiFi();
  }

// ร้องขอ timestamps ด้วยคำสั่ง update
  timeClient.update();
// get ค่าวินาที นาที ชั่วโมง ไปเก็บไว้ในตัวแปร
//  secondNow = timeClient.getSeconds();
  minuteNow = timeClient.getMinutes();
//  hourNow = timeClient.getHours();

  showlcd("  This is Time", String(timeClient.getFormattedTime()));
  if(minuteNow == 36)
  {
    lcd.noBacklight();
    showlcd("  noBacklight", String(timeClient.getFormattedTime()));
  }
  else if (minuteNow == 39)
  {
    lcd.backlight();
    showlcd("  This is Time", String(timeClient.getFormattedTime()));
  }

}
