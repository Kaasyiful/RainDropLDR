#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <TimeLib.h>
#include <ESP8266Firebase.h>

#define LDRPin D8
#define RDPin A0
#define buzzpin D5
#define ssid "Samsung GA 53 5G" //nama wifi
#define katasandi "aaaaaaaaaaa" //kata sandi dari wifi tersebut
#define RefFirebase "https://raindropldr-new-default-rtdb.asia-southeast1.firebasedatabase.app/"

LiquidCrystal_I2C lcd(0x27, 16, 2);
Firebase firebase(RefFirebase);
time_t hujanTerakhir;

void reconnectDisplay()
{
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("Wifi belum terhubung");
    lcd.setCursor(15, 0);
    lcd.print("X");
  }
  Serial.println("Wifi terhubung");
  lcd.setCursor(15, 0);
  lcd.print("C");
}

void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(115200);

  pinMode(LDRPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  lcd.begin();
  lcd.clear();
  lcd.backlight();
  hujanTerakhir = now();

  WiFi.begin(ssid, katasandi);
  reconnectDisplay();
  WiFi.mode(WIFI_STA);
}

void LEDloop() 
{
  digitalWrite(LED_BUILTIN, LOW);
  delay(50);
  digitalWrite(LED_BUILTIN, HIGH);
}

void lightDetect(String strWaktu, bool masukanCahaya)
{
  lcd.setCursor(0, 0);
  Serial.print("Cahaya pada" + strWaktu + "\t: ");
  lcd.print("Cahaya: ");

  lcd.setCursor(8, 0);
    lcd.print("      ");
  if (masukanCahaya == HIGH) {
    Serial.println("Gelap");
    lcd.setCursor(8, 0);
    lcd.print("Gelap");
  } else {
    Serial.println("Terang");
    lcd.setCursor(8, 0);
    lcd.print("Terang");
  }
}

int rainDetect(time_t sekarang, int masukanHujan)
{
  int hariKering = 0;
  Serial.print("Hari setelah hujan terahkir:\t");
  lcd.setCursor(0, 1);
  lcd.println("     ");

  if(masukanHujan >= 2.5)
  {
    Serial.println("0");
    hujanTerakhir = sekarang;
    lcd.setCursor(0, 1);
    lcd.print("Hujan");
    if(second() == 0)
      hariKering = 0;
      
  }
  else if(masukanHujan < 2.5)
  {
    hujanTerakhir = sekarang;
    lcd.setCursor(0, 1);
    lcd.print("Kering u/ " + String(hariKering) + "h");
    if(second() == 0)
      hariKering = minute(sekarang - hujanTerakhir);
  }
  return hariKering;
}

void PushFirebase(time_t sekarang, String strWaktu, bool masukanCahaya, float masukanHujan)
{
  if (second() == 0)
  {
    firebase.setInt(strWaktu + "/cahaya", masukanCahaya);
    firebase.setInt(strWaktu + "/hujan", masukanHujan);
  }
}

void loop() 
{
  // put your main code here, to run repeatedly:
  time_t sekarang = now();
  String StrWaktu = String(year()) + "-" + String(month()) + "-" + String(day()) + String(hour()) + String(minute());
  reconnectDisplay();
  LEDloop();
  
  int MasukanHujan = analogRead(RDPin);
  bool MasukanCahaya = digitalRead(LDRPin);
  lightDetect(StrWaktu, MasukanCahaya);
  int waktuKering = rainDetect(sekarang, MasukanCahaya);
  if(waktuKering > 10)
  {
    int detik = second(now());
    while(detik %= 5) tone(buzzpin, 440, 2);
  }

  PushFirebase(sekarang, StrWaktu, MasukanCahaya, MasukanHujan);
  delay(1000);
}
