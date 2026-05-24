// 1. BLYNK SETTINGS (Copy these from your Blynk Dashboard)
#define BLYNK_TEMPLATE_ID "TMPL6AbCdEfg"
#define BLYNK_TEMPLATE_NAME "IV Bag monitoring"
#define BLYNK_AUTH_TOKEN "RlVwer4Orc5l7iUu94AS0SC-SJMqlkvC"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h> // Updated for ESP32
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

// --- Pin Definitions for ESP32 ---
#define DOUT 32 
#define CLK  33 
#define BUZZER 25 

// --- Initialize Components ---
LiquidCrystal_I2C lcd(0x27, 16, 2); 
HX711 scale;
BlynkTimer timer;

// --- Network Credentials ---
char ssid[] = "Redmi Note 10 Pro";     
char pass[] = "Moon2401"; 

// --- Variables ---
float weight;
float calibration_factor = 102500; // Adjust this during your demo
bool alertSent = false; 

void measureweight() {
  weight = scale.get_units(5);
  if (weight < 0) weight = 0.00;

  // Logic: 0.5kg weight = 500mL volume
  int liter = weight * 1000; 
  int val = map(liter, 0, 500, 0, 100); 
  val = constrain(val, 0, 100);

  // LCD Update
  lcd.setCursor(0, 0);
  lcd.print("IV Vol: ");
  lcd.print(liter);
  lcd.print(" mL    "); 

  lcd.setCursor(0, 1);
  lcd.print("Level:  ");
  lcd.print(val);
  lcd.print(" %     "); 

  // Alert Logic: 20% Threshold
  if (val <= 20) {
    digitalWrite(BUZZER, HIGH);
    if (!alertSent) {
      Blynk.logEvent("iv_alert", "Warning: IV Bottle LOW!");
      alertSent = true; 
    }
  } else {
    digitalWrite(BUZZER, LOW);
    alertSent = false; 
  }

  // IoT Update
  Blynk.virtualWrite(V0, liter);
  Blynk.virtualWrite(V1, val);
  
  Serial.print("Weight: ");
  Serial.print(weight);
  Serial.println(" kg");
}

void setup() {
  Serial.begin(115200);

  // Initialize I2C for ESP32 (Default SDA=21, SCL=22)
  Wire.begin(21, 22); 

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("ESP32 IV System");

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);

  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor); 
  scale.tare(); 

  // Connecting to Blynk
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, measureweight);
}

void loop() {
  Blynk.run();
  timer.run(); 
}
