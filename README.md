# 💉 Smart IV Bag Monitoring System

![Project Status](https://img.shields.io/badge/Status-Completed-brightgreen)
![Platform](https://img.shields.io/badge/Platform-ESP32-blue)
![IoT](https://img.shields.io/badge/IoT-Blynk-purple)
![License](https://img.shields.io/badge/License-MIT-yellow)

> An IoT-based smart system that monitors IV fluid levels in real time and alerts nurses automatically when the bag is running low — reducing manual errors and preventing medical risks.

---

## 📌 Table of Contents

- [Overview](#overview)
- [Problem Statement](#problem-statement)
- [Features](#features)
- [System Architecture](#system-architecture)
- [Hardware Components](#hardware-components)
- [Circuit Connections](#circuit-connections)
- [Software & Libraries](#software--libraries)
- [Blynk Setup](#blynk-setup)
- [How to Run](#how-to-run)
- [Project Demo](#project-demo)
- [Team](#team)
- [License](#license)

---

## 📖 Overview

In hospitals, 80–90% of patients receive IV therapy. With one nurse monitoring 8–12 patients in ICU wards, manual checking of IV bags leads to delays, errors, and in critical cases, risks like air entering the bloodstream or blood backflow.

This project provides an **automated, real-time IV bag monitoring system** using an **ESP32 microcontroller**, a **load cell sensor**, and the **Blynk IoT platform**. It continuously measures IV fluid weight, displays the level on an LCD, and sends an instant alert when the fluid falls below a critical threshold.

---

## 🚨 Problem Statement

- 15–20% of IV bottle replacements are delayed due to manual checking
- An empty IV bag risks **air embolism**, **medication interruption**, and **blood backflow**
- ICU and unconscious patients are especially vulnerable
- Nurses cannot continuously monitor every patient at once

---

## ✨ Features

- ⚖️ **Real-time weight measurement** using HX711 load cell amplifier
- 📺 **LCD display** showing current volume (mL) and fill level (%)
- 🔔 **Buzzer alert** when IV level drops to ≤ 10%
- 📱 **Blynk IoT notification** sent to nurse's smartphone
- 📡 **Remote monitoring** via Wi-Fi (ESP32)
- 🔁 **Auto-reset** of alert once IV bag is replaced (level ≥ 90%)

---

## 🏗️ System Architecture

```
[IV Bag]
   |
[Load Cell]
   |
[HX711 Amplifier] ──► [ESP32]  ──► [LCD Display (I2C)]
                          |
                       [Wi-Fi]
                          |
                     [Blynk Cloud] ──► [Nurse's Phone]
                          |
                      [Buzzer Alert]
```

**Modules:**
- **Module 1 – Sensor Module:** Load cell measures IV fluid weight accurately
- **Module 2 – Controller Module:** ESP32 processes real-time data and applies threshold algorithm
- **Module 3 – Alert Module:** Buzzer + Blynk IoT push notification to nurse

---

## 🔧 Hardware Components

| Component | Description | Quantity |
|---|---|---|
| ESP32 Dev Board | Wi-Fi + Bluetooth microcontroller | 1 |
| Load Cell (500g) | Measures IV bag weight | 1 |
| HX711 Module | Load cell amplifier & ADC | 1 |
| I2C LCD 16x2 (0x27) | Displays volume and level | 1 |
| Buzzer (Active) | Audio alert when level is low | 1 |
| Jumper Wires | Male-to-Male / Male-to-Female | As needed |
| Breadboard / PCB | Circuit prototyping | 1 |
| 5V USB Power Supply | Powers ESP32 | 1 |

---

## 🔌 Circuit Connections

| Component | ESP32 Pin |
|---|---|
| HX711 – DOUT | GPIO 32 |
| HX711 – CLK | GPIO 33 |
| Buzzer (+) | GPIO 25 |
| LCD – SDA | GPIO 21 |
| LCD – SCL | GPIO 22 |
| HX711 – VCC | 3.3V |
| HX711 – GND | GND |
| LCD – VCC | 5V |
| LCD – GND | GND |
| Buzzer (–) | GND |

> 📷 *Add your circuit diagram image here: `docs/circuit_diagram.png`*

---

## 💻 Software & Libraries

### Arduino IDE Libraries Required

Install these via **Arduino Library Manager** (`Sketch → Include Library → Manage Libraries`):

| Library | Purpose |
|---|---|
| `Blynk` | IoT cloud connectivity |
| `WiFi` (built-in ESP32) | Wi-Fi connection |
| `LiquidCrystal_I2C` | I2C LCD display control |
| `HX711` | Load cell amplifier communication |
| `Wire` (built-in) | I2C communication |

### Board Setup

1. Open Arduino IDE → `File → Preferences`
2. Add to "Additional Board Manager URLs":
   ```
   https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
   ```
3. Go to `Tools → Board → Board Manager` → Search **ESP32** → Install

---

## 📱 Blynk Setup

1. Download the **Blynk IoT** app (iOS / Android)
2. Create a new **Template**:
   - Template Name: `IV Bag Monitoring`
   - Hardware: **ESP32**
   - Connection Type: **Wi-Fi**
3. Add **Datastreams**:
   - `V0` → Integer → Volume (mL) — Range: 0 to 500
   - `V1` → Integer → Level (%) — Range: 0 to 100
4. Add **Event**: `iv_alert` → "Warning! IV Bottle Empty"
5. Copy your **Template ID**, **Template Name**, and **Auth Token**

---

## ▶️ How to Run

1. **Clone this repository:**
   ```bash
   git clone https://github.com/your-username/Smart-IV-Bag-Monitoring-System.git
   ```

2. **Open the code:**
   - Navigate to `code/iv_monitor.ino` and open in Arduino IDE

3. **Configure your credentials** in the code:
   ```cpp
   #define BLYNK_TEMPLATE_ID   "YOUR_TEMPLATE_ID"
   #define BLYNK_TEMPLATE_NAME "IV Bag monitoring"
   #define BLYNK_AUTH_TOKEN    "YOUR_AUTH_TOKEN"

   char ssid[] = "YOUR_WIFI_SSID";
   char pass[] = "YOUR_WIFI_PASSWORD";
   ```

4. **Calibrate the load cell:**
   - Adjust `calibration_factor` for your specific load cell
   - Start with `20000` and tune it using known weights

5. **Upload:**
   - Select Board: `ESP32 Dev Module`
   - Select correct COM Port
   - Click **Upload**

6. **Open Serial Monitor** at `115200 baud` to watch live readings

---

## 🎯 Alert Logic

| Level | Status | Action |
|---|---|---|
| ≤ 10% | ⚠️ CRITICAL / EMPTY | Buzzer ON + Blynk alert sent |
| 11% – 89% | ✅ NORMAL | Volume & Level shown on LCD |
| ≥ 90% | 💧 FULL | "IV BAG: FULL" displayed, Buzzer OFF |

---

## 📸 Project Demo

> *Add photos of your prototype here*

| Prototype | Blynk Dashboard |
|---|---|
| `images/prototype_photo.jpg` | `images/blynk_dashboard.png` |

---

## 🏫 Team

**Mini Project – EC2353 (2025)**
Department of Electronics and Communication Engineering

| Role | Name |
|---|---|
| Student | Nivedhita A (ECE B) |
| Guide | Dr. R. Suresh Babu, Professor & Head / ECE |

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

---

> ⭐ If you found this project helpful, give it a star on GitHub!
