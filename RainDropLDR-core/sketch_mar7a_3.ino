#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266Firebase.h>

#define LDRPin D8
#define RDPin A0
#define buzzpin D5
#define ssid "Samsung GA 53 5G" //nama wifi
#define katasandi "aaaaaaaaaaa" //kata sandi dari wifi tersebut
#define RefFirebase "https://raindropldr-new-default-rtdb.asia-southeast1.firebasedatabase.app/"

LiquidCrystal_I2C lcd(0x27, 16, 2);
Firebase firebase(RefFirebase);

int pewaktu = 0;
int hujanTerakhir = 0;
int hariKering = 0;

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

void lightDetect(int waktu, bool masukanCahaya)
{
  lcd.setCursor(0, 0);
  Serial.print("Cahaya pada t+" + String(waktu) + "\t: ");
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

int rainDetect(int waktu, int masukanHujan)
{

  Serial.print("Hari setelah hujan terakhir:\t");
  lcd.setCursor(0, 1);
  lcd.println("                ");

  if(masukanHujan <= 700)
  {
    Serial.println("0");
    hujanTerakhir = waktu;
    int hariKering = 0;
    lcd.setCursor(0, 1);
    lcd.print("Hujan");
    if(waktu % 5 == 0)
      hariKering = 0;
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print("Kering u/ " + String(hariKering) + "h");
    if(waktu % 5 == 0)
      hariKering = (waktu - hujanTerakhir) /5;
    Serial.println(hariKering);
  }
  return hariKering;
}

void PushFirebase(int waktu, bool masukanCahaya, float masukanHujan)
{
  if (waktu % 10 == 0)
  {
    firebase.setInt("t+" + String(waktu) + "/cahaya", masukanCahaya);
    firebase.setInt("t+" + String(waktu) + "/hujan", masukanHujan);
  }
}

void loop() 
{
  // put your main code here, to run repeatedly:
  reconnectDisplay();
  LEDloop();
  
  int MasukanHujan = analogRead(RDPin);
  Serial.println(MasukanHujan);
  bool MasukanCahaya = digitalRead(LDRPin);
  lightDetect(pewaktu, MasukanCahaya);
  int waktuKering = rainDetect(pewaktu, MasukanHujan);
  
  if(waktuKering > 3 && MasukanHujan > 700)
  {
    lcd.setCursor(0, 0);
    lcd.println("Perlu Intervensi");
    lcd.setCursor(0, 1);
    lcd.println("Manual");

    if(pewaktu % 5 == 0) tone(buzzpin, 440, 400);
  }

  PushFirebase(pewaktu, MasukanCahaya, MasukanHujan);

  delay(1000);
  pewaktu++;
}
