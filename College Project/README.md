# Smart Kinesio Tape with Motion Sensors and LED Feedback for Real-Time Knee Monitoring

A wearable knee-motion monitoring prototype that combines **Kinesio tape with a reusable ESP32-C3 sensor module** to track knee flexion and extension in real time. The system uses an **MPU6050 IMU** for motion sensing and provides immediate feedback through LEDs.

## Overview

The project is designed to provide a lightweight and wearable approach to knee-motion monitoring.

The electronic module can be attached to the Kinesio tape using Velcro, allowing the electronics to be reused while the tape can be replaced.

## Features

* Real-time knee flexion and extension monitoring
* MPU6050-based motion sensing
* ESP32-C3 microcontroller
* LED-based movement feedback
* Reusable electronic module
* Kinesio tape-based wearable design
* Real-time motion data processing
* Wi-Fi-based data visualization
* Lightweight and portable prototype

## Hardware Components

| Component           | Purpose                                        |
| ------------------- | ---------------------------------------------- |
| **ESP32-C3**        | Main microcontroller and processing unit       |
| **MPU6050**         | Accelerometer and gyroscope for motion sensing |
| **Li-Po Battery**   | Portable power supply                          |
| **Charging Module** | Battery charging                               |
| **LEDs**            | Visual feedback                                |
| **Kinesio Tape**    | Wearable mounting platform                     |
| **Velcro**          | Attaches the reusable electronic module        |

The project documentation identifies the ESP32-C3, MPU6050, Li-Po battery and charging module among the main prototype components.

## System Workflow

```text
        Knee Movement
              │
              ▼
         ┌──────────┐
         │ MPU6050  │
         │   IMU    │
         └────┬─────┘
              │
              │ I²C
              ▼
        ┌───────────┐
        │ ESP32-C3  │
        │ Processing│
        └─────┬─────┘
              │
        ┌─────┴─────┐
        │           │
        ▼           ▼
     LED Feedback   Wi-Fi
                    │
                    ▼
              Web Dashboard
```

## Software

* Arduino IDE
* C/C++
* ESP32-C3
* MPU6050
* I²C communication
* Wi-Fi
* Web interface

## Pin Configuration

| Component   | ESP32-C3 Pin |
| ----------- | ------------ |
| MPU6050 SDA | GPIO 4       |
| MPU6050 SCL | GPIO 5       |
| VCC         | 3.3 V        |
| GND         | GND          |

> Refer to the firmware for the complete and current pin configuration.

## Getting Started

### Requirements

* ESP32-C3 development board
* MPU6050 module
* Arduino IDE
* Required supporting components
* USB cable

### Uploading the Firmware

1. Install the Arduino IDE.
2. Install ESP32 board support.
3. Connect the ESP32-C3 to your computer.
4. Open the firmware:

```text
firmware/smart_knee_monitor.ino
```

5. Select the appropriate ESP32-C3 board.
6. Select the correct COM port.
7. Compile and upload the firmware.
8. Power the device and connect the sensor module.

## Repository Structure

```text
smart-kinesio-tape/
│
├── README.md
│
└── firmware/
    └── smart_knee_monitor.ino
```

## Future Improvements

* Improve motion-angle accuracy and calibration
* Develop a custom PCB
* Further reduce the module size
* Improve battery management
* Add long-term data logging
* Improve the web interface
* Develop mobile application support
* Perform additional validation with different movement patterns

The project documentation also identifies improved motion-analysis algorithms, PCB miniaturization, mobile visualization and broader validation as potential future developments.

## Disclaimer

This project is a **student-developed prototype for educational and experimental purposes**. It is not intended to be used as a medical diagnostic or clinical device.

## Author

**Sanmugappriyan S**

B.E. Electronics and Communication Engineering

Interested in **Digital Electronics, Embedded Systems, VLSI, RTL Design and Hardware Development**.
