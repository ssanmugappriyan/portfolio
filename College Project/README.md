# Smart Kinesio Tape with Motion Sensors and LED Feedback for Real-Time Knee Monitoring

A wearable knee monitoring system designed to track knee joint movement in real time using an **MPU6050 IMU sensor** and **ESP32-C3 microcontroller**. The system provides immediate movement feedback through **LED and vibration indicators** and displays knee-angle data through a **Wi-Fi-enabled web dashboard**.

---

## 📌 Overview

The **Smart Kinesio Tape** combines a conventional kinesio tape with a reusable electronic module for real-time knee movement monitoring.

The system measures knee flexion and extension using an MPU6050 inertial measurement unit. The ESP32-C3 processes the sensor data, estimates the knee angle, evaluates the movement against predefined limits, and provides feedback through LEDs and a vibration motor.

A built-in Wi-Fi access point allows users to connect to the device and view the measured knee angle through a web-based dashboard.

### Key Objectives

* Monitor knee joint movement in real time
* Estimate knee flexion and extension angles
* Provide immediate visual and vibration feedback
* Display movement data through a web interface
* Develop a compact and reusable electronic module
* Separate the reusable electronics from the disposable kinesio tape

---

## ✨ Key Features

* **Real-time knee angle monitoring**
* **MPU6050-based motion sensing**
* **ESP32-C3 microcontroller**
* **Wi-Fi Access Point mode**
* **Real-time web dashboard**
* **LED-based movement status indication**
* **Vibration feedback for warning conditions**
* **Movement quality monitoring**
* **Flexion and extension tracking**
* **Graphical representation of knee-angle data**
* **Reusable electronics module**
* **Replaceable kinesio tape**

---

## 🧩 System Architecture

```text
                 ┌─────────────────────┐
                 │     MPU6050 IMU     │
                 │  Accelerometer +    │
                 │      Gyroscope      │
                 └──────────┬──────────┘
                            │
                            │ I²C
                            ▼
                 ┌─────────────────────┐
                 │      ESP32-C3       │
                 │                     │
                 │ Sensor Processing   │
                 │ Angle Calculation   │
                 │ Movement Detection  │
                 │ Feedback Control    │
                 │ Wi-Fi Web Server    │
                 └───────┬─────┬───────┘
                         │     │
                ┌────────┘     └─────────┐
                ▼                        ▼
        ┌──────────────┐         ┌──────────────┐
        │ LED Feedback │         │ Vibration    │
        │              │         │ Motor        │
        └──────────────┘         └──────────────┘
                         │
                         ▼
                 ┌─────────────────────┐
                 │   Wi-Fi Dashboard   │
                 │                     │
                 │ Knee Angle          │
                 │ Movement Status     │
                 │ Real-time Graph     │
                 └─────────────────────┘
```

---

## 🔧 Hardware Components

| Component                      | Purpose                                      |
| ------------------------------ | -------------------------------------------- |
| **ESP32-C3 Super Mini**        | Main microcontroller and Wi-Fi communication |
| **MPU6050**                    | Measures acceleration and angular velocity   |
| **3.7 V Li-Po Battery**        | Portable power source                        |
| **TP4050 Charging Module**     | Li-Po battery charging                       |
| **LEDs**                       | Visual movement/status feedback              |
| **Coin Vibration Motor**       | Tactile warning feedback                     |
| **Push/Toggle Switch**         | Power control                                |
| **Kinesio Tape**               | Wearable mounting platform                   |
| **Velcro**                     | Attaches reusable electronics module         |
| **TPU/Silicone Encapsulation** | Protective enclosure for electronics         |

---

## 💻 Software & Technologies

* **Arduino IDE**
* **C/C++**
* **ESP32-C3**
* **MPU6050**
* **I²C Communication**
* **Wi-Fi**
* **Embedded Web Server**
* **HTML**
* **CSS**
* **JavaScript**
* **Chart.js**

---

## ⚙️ How It Works

### 1. Motion Sensing

The MPU6050 is positioned on the leg near the knee joint. It continuously measures acceleration and angular velocity.

### 2. Sensor Processing

The ESP32-C3 reads the MPU6050 data through the I²C interface and processes the accelerometer and gyroscope measurements.

A complementary filtering approach is used to obtain a more stable estimation of the knee movement angle.

### 3. Knee Angle Estimation

The processed sensor data is used to estimate the knee flexion/extension angle.

The system primarily monitors the axis corresponding to knee movement while also evaluating unwanted movement on other axes.

### 4. Movement Evaluation

The measured angle is compared with predefined movement limits.

Depending on the detected movement, the system can provide:

* Normal movement indication
* Warning indication
* Vibration feedback
* Movement-quality indication

### 5. Web Dashboard

The ESP32-C3 operates in **Wi-Fi Access Point mode**, allowing a phone or computer to connect directly to the device.

The dashboard displays the knee movement data and provides a graphical representation of the measured angle.

---

## 📊 Web Dashboard

The web interface is designed to provide a simple real-time view of the user's knee movement.

### Dashboard Features

* Patient/user information
* Current knee angle
* Target angle
* Movement status
* Real-time knee-angle graph
* Movement-quality indication
* Continuous sensor data updates

> Dashboard screenshots will be added here.

```text
/images/dashboard.png
```

---

## 🔌 ESP32-C3 Connections

| Device          | ESP32-C3                  |
| --------------- | ------------------------- |
| MPU6050 SDA     | GPIO 4                    |
| MPU6050 SCL     | GPIO 5                    |
| VCC             | 3.3 V                     |
| GND             | GND                       |
| Vibration Motor | GPIO 10                   |
| LED indicators  | As configured in firmware |

> Pin assignments may vary depending on the hardware revision.

---

## 📁 Repository Structure

```text
smart-kinesio-tape/
│
├── firmware/
│   └── smart_knee_monitor.ino
│
├── web_dashboard/
│   ├── index.html
│   ├── style.css
│   └── script.js
│
├── hardware/
│   ├── circuit/
│   ├── wiring/
│   └── components.md
│
├── images/
│   ├── prototype.jpg
│   ├── circuit.jpg
│   └── dashboard.jpg
│
├── documentation/
│   ├── project_report.pdf
│   └── project_presentation.pdf
│
├── README.md
└── LICENSE
```

---

## 🚀 Getting Started

### Requirements

* ESP32-C3 development board
* MPU6050 IMU
* Arduino IDE
* USB cable
* Required electronic components
* 3.7 V Li-Po battery for portable operation

### Arduino Setup

1. Install the **Arduino IDE**.
2. Install ESP32 board support.
3. Connect the ESP32-C3 to the computer.
4. Open the firmware located in:

```text
firmware/smart_knee_monitor.ino
```

5. Select the appropriate ESP32-C3 board.
6. Select the correct COM port.
7. Compile and upload the firmware.

### Connecting to the Dashboard

After the firmware starts:

1. Power on the device.
2. Connect a phone or computer to the ESP32-C3 Wi-Fi network.
3. Open the device's local web address in a browser.
4. Place the sensor correctly on the leg.
5. Perform knee flexion and extension movements.
6. Observe the real-time angle and movement status on the dashboard.

---

## 🧪 Movement Monitoring

The firmware includes parameters for controlling the motion-monitoring algorithm.

Example parameters:

```cpp
#define ACC_SENS 16384.0
#define GYRO_SENS 131.0
#define ALPHA 0.98
#define MAX_KNEE_ANGLE 140.0
```

These parameters can be modified depending on the sensor configuration and desired operating range.

---

## 🔋 Power System

The prototype uses a rechargeable **3.7 V Li-Po battery**.

```text
Li-Po Battery
      │
      ▼
TP4050 Charging Module
      │
      ▼
ESP32-C3 + Sensor + Feedback Components
```

The electronics module is designed to be reusable while the kinesio tape can be replaced for subsequent use.

---

## 🛠️ Future Improvements

* Improve sensor calibration and angle accuracy
* Add automatic sensor calibration
* Develop a dedicated PCB
* Reduce overall module size
* Improve battery management
* Add data logging
* Add cloud-based monitoring
* Develop mobile application support
* Support additional joint-movement monitoring
* Improve enclosure and wearable ergonomics
* Perform more extensive movement validation

---

## ⚠️ Disclaimer

This project is a **student-developed prototype for educational and experimental purposes**. It is intended to demonstrate wearable motion sensing and real-time feedback and should not be considered a medical diagnostic or clinical device.

---

## 📷 Project Images

### Prototype

> Add prototype photograph here.

### Electronics Module

> Add electronics/module photograph here.

### Web Dashboard

> Add dashboard screenshot here.

### Wearable Setup

> Add photograph showing the sensor placement and kinesio tape here.

---

## 📚 Project Documentation

Additional project documentation can be found in the `documentation/` directory.

* Project Report
* Project Presentation
* Hardware Documentation
* Firmware Documentation

---

## 👨‍💻 Author

**Sanmugappriyan S**

Final-year **B.E. Electronics and Communication Engineering**

Interested in **Digital Electronics, Embedded Systems, VLSI, RTL Design and Hardware Development**.

---

## 📄 License

This project is available for educational and personal use. See the `LICENSE` file for details.
