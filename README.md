# STM32 Temperature & Humidity Data Logger

This project is a **temperature and humidity monitoring and logging system** based on the **STM32F103C8T6** microcontroller.
It reads environmental data from a sensor, displays it on an OLED screen, logs it to an SD card with date and time, and sends system status information to a PC via UART.

---

## 🧠 Hardware Specifications

- **Microcontroller:** STM32F103C8T6
- **Temperature & Humidity Sensor:** SHT3X
- **Display:** OLED (I2C interface)
- **Storage:** SD Card (SPI interface)
- **Indicators:**
  - Green LED – Sensor connected successfully
  - Red LED – Sensor connection error
- **PC Communication:** UART (Serial)

---

## 🔌 Communication Interfaces

| Module | Interface |
|------|----------|
| SHT3X Sensor | I2C |
| OLED Display | I2C |
| SD Card | SPI |
| PC Communication | UART |

---

## ⚙️ Project Functionality

- Reads **temperature and humidity** data from the SHT3X sensor via I2C
- Displays real-time temperature and humidity values on the OLED display
- Stores temperature, humidity, **date**, and **time** on an SD card
- Data is saved in **CSV file format**
- Uses the **internal RTC of the STM32** for date and time tracking
- Sends sensor data and system status messages to a PC via UART

---

## 💾 Data Logging Format (CSV)

Date,Time,Temperature,Humidity
2025-01-05,14:32:10,25.6,45.2
