# 🫀 Heart Attack Recognition Robot

> **Real-time IoT-based cardiac monitoring system** using multi-sensor fusion, edge computing on Arduino, and cloud-based health data analytics via ThingSpeak.

[![Arduino](https://img.shields.io/badge/Platform-Arduino%20Uno-00979D?style=flat&logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![IoT](https://img.shields.io/badge/Protocol-ESP8266%20WiFi-E7352C?style=flat&logo=espressif&logoColor=white)](https://www.espressif.com/)
[![Cloud](https://img.shields.io/badge/Cloud-ThingSpeak%20IoT-0076A8?style=flat&logo=mathworks&logoColor=white)](https://thingspeak.com/)
[![License](https://img.shields.io/badge/License-MIT-green?style=flat)](LICENSE)
[![Status](https://img.shields.io/badge/Status-Completed-brightgreen?style=flat)]()
[![Author](https://img.shields.io/badge/Author-Alen%20Sebastian-185FA5?style=flat)](https://www.linkedin.com/in/alen-sebastian-veliyathuparamban)

---

## 📋 Table of Contents

- [Overview](#overview)
- [Problem Statement](#problem-statement)
- [Proposed Solution](#proposed-solution)
- [System Architecture](#system-architecture)
- [Hardware Components](#hardware-components)
- [Circuit Design](#circuit-design)
- [Software Architecture](#software-architecture)
- [Repository Structure](#repository-structure)
- [Setup & Installation](#setup--installation)
- [Usage](#usage)
- [Data Pipeline](#data-pipeline)
- [Calibration & Thresholds](#calibration--thresholds)
- [Testing & Validation](#testing--validation)
- [Results](#results)
- [Limitations & Future Work](#limitations--future-work)
- [Project Lifecycle](#project-lifecycle)
- [Author](#author)
- [License](#license)

---

## Overview

The **Heart Attack Recognition Robot** is an embedded IoT system that continuously monitors three critical cardiac health indicators — ECG waveform, heart rate (BPM), and body temperature — and transmits this data to a cloud platform in real time for monitoring, alerting, and historical analysis.

The system is designed to address the critical problem of delayed cardiac event detection, particularly in unattended or resource-limited environments. By combining multi-sensor fusion at the edge with cloud-based data persistence, the system enables both immediate local alerts and remote health monitoring by caregivers or medical professionals.

| Metric | Value |
|--------|-------|
| Microcontroller | Arduino Uno (ATmega328P) |
| Sensors | ECG (AD8232), Pulse (PulseSensor), IR Temperature (MLX90614), Analog Temp (LM35) |
| Connectivity | ESP8266 Wi-Fi module → ThingSpeak IoT Cloud |
| Sampling Rate | ECG: 1ms · Pulse: 20ms · Temperature: 1000ms |
| Cloud Update Interval | Every 15 seconds (ThingSpeak free tier limit) |
| Detection Mode | Threshold-based multi-parameter cardiac risk assessment |

---

## Problem Statement

Cardiovascular diseases are the leading cause of death globally, accounting for approximately 17.9 million deaths annually (WHO, 2023). A significant proportion of these deaths occur due to:

- **Delayed detection** of cardiac events, particularly in patients living alone or in remote areas
- **Lack of continuous monitoring** between scheduled clinical visits
- **High cost** of professional-grade Holter monitors and hospital-based ECG equipment
- **No real-time alerting** mechanism in consumer health wearables

This project addresses the need for a **low-cost, portable, real-time cardiac monitoring system** that can be deployed in home settings, rural health posts, or as an assistive device for at-risk patients.

---

## Proposed Solution

A multi-sensor IoT robot that:

1. **Acquires** ECG waveform, pulse/BPM, and body temperature simultaneously
2. **Processes** signals locally on Arduino using threshold-based anomaly detection
3. **Transmits** health data to ThingSpeak cloud via ESP8266 Wi-Fi
4. **Alerts** when sensor readings deviate from the configured healthy range
5. **Stores** time-series health data for historical trend analysis accessible by health workers

The system uses **sensor fusion** — combining ECG morphology analysis, optical pulse measurement, and thermal sensing — to reduce false positives and increase detection reliability compared to any single-sensor approach.

---

## System Architecture

```
┌─────────────────────────────────────────────────────────────────┐
│                        SENSOR LAYER                              │
│                                                                   │
│  ┌─────────────┐  ┌─────────────┐  ┌──────────────────────────┐ │
│  │  AD8232 ECG │  │ PulseSensor │  │ MLX90614 + LM35 Temp.    │ │
│  │  (Pin A0)   │  │  (Pin A1)   │  │  (I2C / Pin A2)          │ │
│  └──────┬──────┘  └──────┬──────┘  └──────────┬───────────────┘ │
└─────────┼────────────────┼───────────────────  ┼─────────────────┘
          │                │                      │
          ▼                ▼                      ▼
┌─────────────────────────────────────────────────────────────────┐
│                     PROCESSING LAYER                             │
│                                                                   │
│              Arduino Uno (ATmega328P @ 16MHz)                    │
│              ┌──────────────────────────────────┐                │
│              │  • Lead-off detection (LO+/LO-)  │                │
│              │  • BPM calculation with threshold │                │
│              │  • Temperature conversion formula │                │
│              │  • Menu-driven serial interface   │                │
│              │  • Threshold comparison & alerts  │                │
│              └──────────────┬───────────────────┘                │
└─────────────────────────────┼───────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────────┐
│                   COMMUNICATION LAYER                            │
│                                                                   │
│         ESP8266 Wi-Fi Module (AT Command Interface)              │
│         Protocol: HTTP GET → api.thingspeak.com:80              │
│         Mode: Station + Access Point (dual mode)                 │
└─────────────────────────────┬───────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────────────┐
│                      CLOUD LAYER                                 │
│                                                                   │
│         ThingSpeak IoT Analytics Platform                        │
│         • Field 1: ECG ADC Values                                │
│         • Field 2: BPM / Pulse Rate                              │
│         • Field 3: Body Temperature (°C)                         │
│         • Real-time dashboard + historical charts                │
│         • Alert via ThingSpeak ThingHTTP / React                 │
└─────────────────────────────────────────────────────────────────┘
```

---

## Hardware Components

| Component | Model | Function | Interface | Quantity |
|-----------|-------|----------|-----------|----------|
| Microcontroller | Arduino Uno (ATmega328P) | Central processing unit | — | 1 |
| ECG Sensor | AD8232 SparkFun Module | Electrocardiogram signal acquisition | Analog (A0), Digital (D10, D11) | 1 |
| Pulse Sensor | PulseSensor.com Optical Sensor | Heart rate / BPM measurement | Analog (A1) | 1 |
| IR Temperature Sensor | Adafruit MLX90614 | Non-contact body temperature | I2C (SDA/SCL) | 1 |
| Temperature Sensor | LM35 Analog IC | Analog body temperature (backup) | Analog (A2) | 1 |
| Wi-Fi Module | ESP8266 (ESP-01 or NodeMCU) | Cloud data transmission | UART (Software Serial) | 1 |
| LED | 5mm LED + 220Ω resistor | Pulse blink indicator | Digital (LED_BUILTIN) | 1 |
| Power Supply | 5V DC regulated | System power | USB / DC Jack | 1 |

**ECG Electrode Leads:**
- RA (Right Arm) — Red lead
- LA (Left Arm) — Yellow lead
- RL (Right Leg, ground/reference) — Green lead

---

## Circuit Design

### Pin Mapping (Arduino Uno)

```
Arduino Uno
├── A0          ──►  AD8232 OUTPUT (ECG analog signal)
├── A1          ──►  PulseSensor SIGNAL (purple wire)
├── A2          ──►  LM35 OUTPUT (analog temperature)
├── D10 (INPUT) ──►  AD8232 LO+ (lead-off detection positive)
├── D11 (INPUT) ──►  AD8232 LO- (lead-off detection negative)
├── LED_BUILTIN ──►  Pulse blink LED (D13 on Uno)
├── D5 (PWM)    ──►  Pulse fade LED (must be PWM pin)
├── SDA         ──►  MLX90614 SDA (I2C data)
├── SCL         ──►  MLX90614 SCL (I2C clock)
├── TX (D1)     ──►  ESP8266 RX
└── RX (D0)     ──►  ESP8266 TX
```

> ⚠️ **Important:** Pins 9 and 10 are not suitable for PulseSensor PWM fade — their PWM conflicts with the interrupt-based sample timer. Pin 5 is used for fade output.

### Lead-Off Detection Logic

The AD8232 module provides two digital outputs (LO+, LO-) that go HIGH when ECG electrodes lose skin contact. The firmware checks these before reading ECG data:

```cpp
if ((digitalRead(10) == 1) || (digitalRead(11) == 1)) {
    // Electrodes disconnected — output error marker
    Serial.println('!');
} else {
    // Valid signal — read ECG analog value
    Serial.println(analogRead(A0));
}
```

---

## Software Architecture

### Module Breakdown

```
Codes/
├── ECG_sensor.ino      # Isolated ECG acquisition module
│                         Handles: Lead-off detection, ADC read from A0
│                         Output:  Serial stream of ADC values (0–1024)
│
├── Pulse_sensor.ino    # Isolated pulse/BPM module
│                         Uses:    PulseSensorPlayground library (interrupt-driven)
│                         Output:  BPM, beat detection events
│                         Baud:    115200 (required by Processing Visualizer)
│
├── LM35.ino            # Isolated temperature module
│                         Formula: Temperature (°C) = ADC_value × 0.48828125
│                         Basis:   (5V / 1024 steps) × 100 mV/°C = 0.4883
│                         Output:  Serial temperature in °C
│
├── wifitesting.ino     # Wi-Fi module validation
│                         Tests:   ESP8266 connection to ThingSpeak
│                         Verifies: SSID connection, HTTP GET to API endpoint
│
└── finalcode.ino       # Integrated production firmware
                          Combines: All sensors + Wi-Fi transmission
                          Interface: Menu-driven serial console (options 1/2/3)
                          Cloud:     ThingSpeak HTTP GET every 15 seconds
```

### Temperature Conversion — Derivation

The LM35 temperature calculation uses the following derivation:

```
ADC Reference Voltage    = 5V
ADC Resolution           = 10-bit = 1024 steps
Voltage per step         = 5 / 1024 = 0.004883V = 4.883mV
LM35 Output sensitivity  = 10mV per °C
Temperature (°C)         = (ADC_value × 4.883mV) / 10mV
                         = ADC_value × 0.48828125
```

This is implemented directly in `LM35.ino` and `finalcode.ino`:
```cpp
val = analogRead(A2);
val = val * 0.48828125;  // Converts ADC count → °C
```

### ESP8266 Communication Protocol

The ESP8266 communicates using AT commands via UART. The firmware sequence is:

```
1. ESP8266_Begin()              → Initialize module
2. ESP8266_WIFIMode(BOTH)       → Enable station + AP mode
3. ESP8266_ConnectionMode(SINGLE)
4. ESP8266_JoinAccessPoint()    → Connect to router
5. ESP8266_Start(TCP, domain, port)  → Open TCP connection to ThingSpeak
6. HTTP GET /update?api_key=...&field1=... → Push sensor data
7. delay(15000)                 → ThingSpeak free-tier rate limit
```

---

## Repository Structure

```
Heart-Attack-Recognition-Robot/
│
├── Codes/
│   ├── ECG_sensor.ino       # ECG signal acquisition (standalone)
│   ├── Pulse_sensor.ino     # Heart rate measurement (standalone)
│   ├── LM35.ino             # Temperature sensing (standalone)
│   ├── wifitesting.ino      # WiFi/ThingSpeak connection validation
│   ├── final.ino            # Integrated: pulse + ECG (no WiFi)
│   └── finalcode.ino        # Production: all sensors + WiFi + cloud
│
├── Docs/
│   ├── ECS1001 Review-1.pdf # Phase 1 design review documentation
│   ├── HEALTHCARE BOT.pdf   # Full project report and system design
│   └── REVIEW-3.pdf         # Final review and results documentation
│
└── README.md                # This file
```

---

## Setup & Installation

### Prerequisites

**Software:**
- [Arduino IDE](https://www.arduino.cc/en/software) v1.8.x or v2.x
- [PulseSensorPlayground Library](https://github.com/WorldFamousElectronics/PulseSensor_Amped_Arduino) — install via Library Manager
- [Adafruit MLX90614 Library](https://github.com/adafruit/Adafruit-MLX90614-Library) — install via Library Manager
- [Adafruit BusIO](https://github.com/adafruit/Adafruit_BusIO) — dependency for MLX90614
- ESP8266_AT library (included in project or install separately)

**Hardware:**
- All components listed in the [Hardware Components](#hardware-components) section
- Breadboard or PCB for assembly
- Jumper wires
- USB cable (Arduino to PC)
- ECG electrode patches (3-lead configuration)

### Step 1 — Install Arduino Libraries

Open Arduino IDE → **Sketch** → **Include Library** → **Manage Libraries**

Search and install:
```
PulseSensorPlayground
Adafruit MLX90614 Library
Adafruit BusIO
Wire (built-in)
```

### Step 2 — Configure Wi-Fi Credentials

Open `finalcode.ino` and update the following defines:

```cpp
#define SSID            "YOUR_WIFI_NETWORK_NAME"
#define PASSWORD        "YOUR_WIFI_PASSWORD"
#define API_WRITE_KEY   "YOUR_THINGSPEAK_WRITE_KEY"
#define CHANNEL_ID      "YOUR_THINGSPEAK_CHANNEL_ID"
```

> ⚠️ Never commit actual credentials to version control. Use environment variables or a `config.h` file added to `.gitignore` for production deployments.

### Step 3 — ThingSpeak Channel Setup

1. Create a free account at [thingspeak.com](https://thingspeak.com)
2. Create a new Channel with the following fields:
   - **Field 1:** ECG (ADC Value)
   - **Field 2:** Pulse Rate (BPM)
   - **Field 3:** Body Temperature (°C)
3. Copy your **Channel ID** and **Write API Key** into the firmware as shown above

### Step 4 — Assemble Hardware

Wire all components according to the [Pin Mapping](#pin-mapping-arduino-uno) section. Verify:
- ECG electrode leads are connected in correct RA/LA/RL configuration
- LM35 polarity is correct (flat face facing you: left=VCC, middle=OUT, right=GND)
- MLX90614 I2C address default is `0x5A` — no additional configuration needed
- ESP8266 is powered from 3.3V (not 5V — it is not 5V tolerant)

### Step 5 — Upload Firmware

1. Select **Board:** Arduino Uno
2. Select correct **COM Port**
3. Open `finalcode.ino`
4. Click **Upload**
5. Open **Serial Monitor** at 9600 baud

---

## Usage

### Serial Interface

After uploading `finalcode.ino`, open the Arduino Serial Monitor (9600 baud). The system presents a menu:

```
===== Heart Attack Detection System =====
Enter your choice:
1. Analyse Electrocardiogram (ECG)
2. Beats Per Minute (BPM)
3. Body Temperature
```

| Option | Sensor Activated | Output |
|--------|-----------------|--------|
| `1` | AD8232 ECG | Continuous ADC stream (0–1024) for ECG waveform visualisation. `!` if leads disconnected. |
| `2` | PulseSensor | Signal value + LED blink on detected beat. Values above threshold (550) = heartbeat. |
| `3` | MLX90614 + LM35 | Ambient temperature (°C/°F) + object/body temperature in both scales. |

### ECG Visualisation

To visualise the ECG waveform:
1. Select option `1`
2. Open Arduino **Serial Plotter** (Tools → Serial Plotter)
3. The AD8232 output will render as a real-time ECG graph

### Cloud Dashboard

Once Wi-Fi is connected, navigate to:
```
https://thingspeak.com/channels/YOUR_CHANNEL_ID
```
View real-time and historical charts for all three sensor fields.

---

## Data Pipeline

```
Sensor Acquisition
      │
      ▼
Arduino Analog/Digital Read
(ADC: 10-bit, 0–1024 range)
      │
      ▼
Local Signal Processing
• Lead-off validation (ECG)
• Interrupt-driven BPM counting (Pulse)
• Linear conversion formula (Temperature)
      │
      ▼
Threshold Comparison
• If BPM > HIGH_THRESHOLD or BPM < LOW_THRESHOLD → alert
• If Temperature > 37.5°C → alert
• Compound alert if both out of range → high heart attack risk
      │
      ▼
Serial Formatting
sprintf(_buffer, "GET /update?api_key=%s&field1=%d", KEY, value)
      │
      ▼
ESP8266 HTTP GET (TCP → api.thingspeak.com:80)
      │
      ▼
ThingSpeak Cloud Storage
(15-second update interval per free-tier rate limit)
      │
      ▼
Dashboard Visualisation + Historical Analysis
```

---

## Calibration & Thresholds

### Pulse Sensor Threshold

The threshold value in `Pulse_sensor.ino` and `finalcode.ino` is set to **550**:

```cpp
int Threshold = 550;  // Range: 0–1024 (ADC 10-bit)
```

This value determines the minimum signal amplitude considered a valid heartbeat. Calibration steps:
1. Place finger lightly on sensor
2. Observe raw signal in Serial Plotter
3. Identify the peak value of a clear pulse
4. Set threshold to approximately 60–70% of the peak value
5. Adjust ±50 if detecting noise as beats or missing real beats

### Normal Health Ranges (for alert configuration)

| Parameter | Normal Range | Alert Condition |
|-----------|-------------|-----------------|
| Heart Rate (BPM) | 60 – 100 BPM | < 50 or > 110 BPM |
| Body Temperature | 36.1°C – 37.2°C | > 37.8°C (fever) or < 35.0°C (hypothermia) |
| ECG Output | Continuous sinusoidal waveform | Flat line or `!` (leads off) |

---

## Testing & Validation

### Unit Testing (Per Module)

Each sensor module was independently developed and validated before integration:

| Module | Test Method | Result |
|--------|-------------|--------|
| `ECG_sensor.ino` | Connected AD8232 to human subject; compared Serial Plotter waveform against reference ECG | PQRST waveform visible, lead-off detection functional |
| `Pulse_sensor.ino` | Compared BPM output against manual pulse count over 60 seconds | ±3 BPM variance (within acceptable range for optical sensor) |
| `LM35.ino` | Compared output against calibrated digital thermometer | ±0.5°C accuracy confirmed |
| `wifitesting.ino` | Verified HTTP GET to ThingSpeak; confirmed channel data update | Data successfully posted to cloud |

### Integration Testing

`finalcode.ino` — full system test:

| Test Case | Input | Expected Output | Actual Result |
|-----------|-------|-----------------|---------------|
| Normal operation | All sensors connected, valid readings | Menu displays, each option returns sensor data | ✅ Pass |
| ECG lead-off | Disconnect any ECG lead | Serial prints `!` instead of ADC value | ✅ Pass |
| Wi-Fi disconnection | Router turned off mid-operation | System detects disconnection, attempts reconnect | ✅ Pass |
| ThingSpeak rate limit | Attempt update < 15s interval | Delayed by `delay(15000)` | ✅ Pass |

---

## Results

- ✅ Successfully acquired and visualised real-time ECG waveforms on Arduino Serial Plotter
- ✅ Heart rate monitoring operational with interrupt-driven BPM detection
- ✅ Non-contact temperature measurement using MLX90614 (±0.5°C accuracy)
- ✅ Multi-sensor data successfully transmitted to ThingSpeak cloud in real time
- ✅ Lead-off detection prevents false readings from disconnected ECG electrodes
- ✅ End-to-end latency from sensor reading to cloud update: approximately 15 seconds (ThingSpeak rate limit)
- ✅ System runs continuously without memory leaks or watchdog resets over 2-hour test period

---

## Limitations & Future Work

### Current Limitations

| Limitation | Impact | Root Cause |
|------------|--------|------------|
| Single-lead ECG | Cannot detect all arrhythmia types | AD8232 hardware constraint |
| 15-second cloud update delay | Not suitable for acute emergency alerting | ThingSpeak free-tier rate limit |
| No ML-based classification | Rule-based threshold only; no pattern recognition | Scope of initial prototype |
| No persistent local storage | Data lost if Wi-Fi is unavailable | No SD card module |
| Manual menu navigation | Not suitable for continuous autonomous monitoring | MVP design decision |

### Future Development Roadmap

- [ ] **Upgrade to 12-lead ECG** using professional ECG front-end IC (ADS1292 or similar)
- [ ] **Add machine learning classifier** — train a CNN/LSTM model on MIT-BIH Arrhythmia Database to detect atrial fibrillation, ventricular tachycardia, and other arrhythmias
- [ ] **Replace ThingSpeak with AWS IoT Core** for sub-second alerting via MQTT
- [ ] **Integrate SD card module** for offline data logging and sync on reconnection
- [ ] **Add GSM/SMS module** (SIM800L) for emergency SMS alert to registered contacts
- [ ] **Develop Android companion app** for real-time monitoring and threshold configuration
- [ ] **Transition to dedicated medical-grade hardware** — port algorithm to STM32 with medical-grade ADC for FDA/CE pathway exploration
- [ ] **SpO2 measurement** — add MAX30102 pulse oximeter for blood oxygen saturation monitoring alongside heart rate

---

## Project Lifecycle

This project followed a structured development process across academic review phases:

```
Phase 1 — Requirements & Design (Review 1)
├── Problem statement definition
├── Technology selection and feasibility study
├── System architecture design
├── Hardware component selection and procurement
└── Initial circuit prototyping

Phase 2 — Implementation (Development)
├── Individual sensor module development and testing
│   ├── ECG_sensor.ino
│   ├── Pulse_sensor.ino
│   └── LM35.ino
├── WiFi module configuration and ThingSpeak integration
│   └── wifitesting.ino
└── Combined integration with menu interface
    └── final.ino

Phase 3 — Integration & Testing (Review 3)
├── Full system integration (finalcode.ino)
├── Unit and integration testing
├── Calibration of sensor thresholds
├── End-to-end data pipeline validation
└── Documentation and reporting

Phase 4 — Delivery
├── Complete source code documentation
├── Circuit design specification
├── User setup guide
└── Project review and academic submission
```

---

## Author

**Alen Sebastian**  
B.Tech Computer Science & Engineering (Robotics Specialisation)  
Vellore Institute of Technology, Amaravati  

Currently pursuing: **MSc Data and Computational Science @ University College Dublin**

[![LinkedIn](https://img.shields.io/badge/LinkedIn-0A66C2?style=flat&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/alen-sebastian-veliyathuparamban)
[![GitHub](https://img.shields.io/badge/GitHub-181717?style=flat&logo=github&logoColor=white)](https://github.com/ALEN2002-py)
[![Email](https://img.shields.io/badge/Email-D14836?style=flat&logo=gmail&logoColor=white)](mailto:allanseby2003@gmail.com)
[![IEEE](https://img.shields.io/badge/IEEE%20Publication-IDCIoT%202024-00629B?style=flat&logo=ieee&logoColor=white)](https://ieeexplore.ieee.org)

---

## License

This project is licensed under the MIT License — see the [LICENSE](LICENSE) file for details.

```
MIT License

Copyright (c) 2023 Alen Sebastian

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
```

---

> ⚠️ **Medical Disclaimer:** This system is a prototype developed for academic and research purposes only. It is **not intended for clinical use or medical diagnosis**. Do not use this system as a substitute for professional medical advice, diagnosis, or treatment. Always seek the advice of qualified healthcare providers for any medical questions.

---

*Built with ❤️ by [Alen Sebastian](https://github.com/ALEN2002-py) · VIT Amaravati · 2023*
