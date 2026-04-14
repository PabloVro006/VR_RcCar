# 🚗📡 Wireless FPV RC Car System

<p align="center">
  <img src="docs/images/cover.jpg" alt="Project Cover" width="800"/>
</p>

<p align="center">
  <b>Custom steering wheel → PC → STM32 → NRF24L01 → RC Car + FPV Camera</b><br>
  Low-latency wireless control system with real-time video streaming.
</p>

---

## ✨ Features

* 🎮 Steering wheel input via **SDL3 (C)**
* 🔌 USB Serial communication (PC → STM32)
* 📡 NRF24L01 wireless transmission
* ⚡ Low-latency control system
* 🚗 Custom-modified RC car (motor + servo)
* 📷 Live camera streaming over web
* 🥽 VR-ready viewing capability (future extension)

---

## 🧠 System Architecture

<p align="center">
  <img src="docs/images/architecture.png" width="800"/>
</p>

### 🔄 Data Flow

```text
Steering Wheel
      ↓ (USB)
      PC (SDL3 App)
      ↓ (Serial UART)
   STM32 #1 (Transmitter)
      ↓ (NRF24L01 RF)
   STM32 #2 (Receiver)
      ↓
  Motor + Servo Control
      ↓
   Camera Module → Web Stream
```

---

## 🧩 Hardware Components

### 🖥️ Transmitter Side

* PC (Windows)
* Steering Wheel Controller
* STM32 (e.g., STM32F103 / STM32F4)
* NRF24L01 Module

### 🚙 Receiver Side

* STM32
* NRF24L01 Module
* DC Motor Driver (e.g., L298N / BTS7960)
* Servo Motor
* Camera Module (ESP32-CAM / USB cam + SBC)

---

## 🔌 Wiring & Schematics

<p align="center">
  <img src="docs/images/wiring_tx.png" width="400"/>
  <img src="docs/images/wiring_rx.png" width="400"/>
</p>

### NRF24L01 ↔ STM32

| NRF24L01 | STM32      |
| -------- | ---------- |
| VCC      | 3.3V       |
| GND      | GND        |
| CE       | GPIO       |
| CSN      | SPI CS     |
| SCK      | SPI SCK    |
| MOSI     | SPI MOSI   |
| MISO     | SPI MISO   |
| IRQ      | (optional) |

---

## 💻 Software Overview

### 🖥️ PC Application

* Language: **C**
* Library: **SDL3**
* Responsibilities:

  * Read steering wheel input
  * Normalize control signals
  * Send via serial (UART over USB)

---

### 🔁 STM32 Transmitter

* Receives serial data
* Packs into RF payload
* Sends via NRF24L01

---

### 📡 STM32 Receiver

* Receives RF packets
* Decodes control signals
* Drives:

  * Motor (PWM)
  * Servo (PWM)

---

### 📷 Camera Streaming

Depending on your implementation:

#### Option 1: ESP32-CAM (Recommended)

* Hosts its own web server
* Streams MJPEG over WiFi

#### Option 2: USB Camera + SBC (e.g., Raspberry Pi)

* Use:

  * `mjpg-streamer`
  * `ffmpeg`
  * `gstreamer`

---

## 🌐 Live Streaming

Access the stream via browser:

```bash
http://<camera-ip>:<port>
```

Example:

```bash
http://192.168.1.42:8080
```

---

## 🛠️ Build & Setup

### PC Side

```bash
git clone https://github.com/yourusername/yourrepo.git
cd pc-controller
gcc main.c -lSDL3 -o controller
./controller
```

---

### STM32

Use:

* STM32CubeIDE **or**
* PlatformIO

Flash both boards:

* `stm32_tx/` → Transmitter
* `stm32_rx/` → Receiver

---

## 📷 Demo

<p align="center">
  <img src="docs/images/demo.gif" width="700"/>
</p>

---

## 🧪 Future Improvements

* 🥽 VR headset integration (WebXR / OpenVR)
* 📶 Telemetry feedback (speed, battery, signal strength)
* 🧠 Autonomous driving mode
* 📡 Longer range RF (LoRa alternative)
* 🎯 PID tuning for smoother control

---

## ⚠️ Notes

* NRF24L01 requires stable **3.3V** (use a capacitor!)
* Keep antenna orientation consistent
* Minimize RF interference

---

## 📁 Project Structure

```bash
.
├── pc-controller/      # SDL3 application
├── stm32_tx/           # Transmitter firmware
├── stm32_rx/           # Receiver firmware
├── docs/
│   ├── images/
│   └── schematics/
└── README.md
```

---

## 🤝 Contributing

Pull requests are welcome! For major changes, open an issue first.

---

## 📜 License

MIT License

---

## 🙌 Acknowledgements

* STM32 ecosystem
* NRF24L01 community libraries
* SDL project

---

<p align="center">
  Built with ⚡, coffee ☕, and a love for embedded systems
</p>
