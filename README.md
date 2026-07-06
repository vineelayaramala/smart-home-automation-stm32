Smart Home Automation using STM32
📌 Overview

This project demonstrates a Smart Home Automation system built using the STM32 microcontroller. It enables users to control and automate home appliances efficiently using sensors and/or wireless communication modules. The system improves convenience, energy efficiency, and safety by allowing both manual and automated control of devices.

Components Used
Hardware:
STM32 Microcontroller (STM32F103C8T6 / as per your board)
Relay Module
Sensors (PIR / DHT11 / DHT22 / LDR – based on your project)
Wi-Fi Module (ESP8266) / Bluetooth Module (HC-05) (if used)
Bulbs / Fan / Appliances (for demo)
Power Supply (5V/12V)
Software:
STM32CubeIDE
STM32 HAL Drivers
Embedded C

Working Principle

The STM32 microcontroller acts as the central control unit of the system. It collects input from sensors (like motion, temperature, or light sensors) and processes the data to make decisions.

Based on the logic:

If a condition is met → STM32 triggers relay modules
Relays control electrical appliances (ON/OFF)
If wireless module is used → commands are received from a mobile app or cloud

Features
🔌 Control of home appliances using STM32
🌡️ Sensor-based automation (temperature/light/motion)
📱 Optional remote control via Bluetooth/Wi-Fi
⚡ Efficient and low-power embedded system
🛡️ Safe relay-based switching mechanism
🔄 Real-time response system

Project Structure
Smart-Home-Automation-STM32/
│
├── Core/
│   ├── Inc/
│   ├── Src/
│
├── Drivers/
│
├── Middleware/   (if used)
│
├── README.md
└── main.c

Future Scope
🌐 IoT integration with cloud platforms (Firebase/AWS)
📲 Mobile application for full remote control
🗣️ Voice assistant integration (Google Assistant / Alexa)
📊 Energy consumption monitoring
🏠 Expansion to full smart home ecosystem


Author

Vineela Yaramala
Electronics & Communication Engineering
Interested in Embedded Systems & IoT
