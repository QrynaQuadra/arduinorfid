#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MFRC522.h>
#include <SPI.h>

#define RST_PIN         9          // RFID modülünün reset pini
#define SS_PIN          10         // RFID modülünün slave select pini
#define LCD_ADDR        0x27       // LCD'nin I2C adresi

MFRC522 rfid(SS_PIN, RST_PIN);     // RFID modülünün SPI pini
LiquidCrystal_I2C lcd(LCD_ADDR, 16, 2); // I2C LCD ekranı, 16x2 olarak tanımlanmıştır

void setup() {
  Serial.begin(9600);  // Seri haberleşmeyi başlat
  SPI.begin();          // SPI'yi başlat
  rfid.PCD_Init();      // RFID modülünü başlat
  lcd.begin(16, 2);     // LCD ekranını başlat, 16 kolon ve 2 satır
  lcd.backlight();      // LCD arka ışığını aç
  lcd.setCursor(0, 0);
  lcd.print("Hazir");
}

void loop() {
  // RFID kartını oku
  if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    // Kart okunduğunda RFID modülüyle iletişimi kapat
    rfid.PICC_HaltA();
    // Kartın UID'sini al
    String uid = "";
    for (byte i = 0; i < rfid.uid.size; i++) {
      uid += String(rfid.uid.uidByte[i], HEX);
    }
    // Kartın sahibini belirle
    String owner = "";
    if (uid == "XXXXXXXXXXXX") {  // Kartın UID'sini buraya ekle
      owner = "Ali";
    } else if (uid == "YYYYYYYYYYYY") {  // Kartın UID'sini buraya ekle
      owner = "Ayşe";
    } else if (uid == "ZZZZZZZZZZZZ") {  // Kartın UID'sini buraya ekle
      owner = "Ahmet";
    } else if (uid == "WWWWWWWWWWWW") {  // Kartın UID'sini buraya ekle
      owner = "Zeynep";
    } else if (uid == "VVVVVVVVVVVV") {  // Kartın UID'sini buraya ekle
      owner = "Mehmet";
    }
    // LCD ekranına hoş geldiniz mesajını yazdır
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hos Geldiniz");
    lcd.setCursor(0, 1);
    lcd.print(owner);
    // Bekle
    delay(2000);
    // LCD ekranını temizle
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Hazir");
  }
}
