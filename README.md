# ESP32 Display

## Description

This project runs on an ESP32 connected to a small TFT display, controlled using the **TFT_eSPI** library.
The program renders a sky scene with moving aurora borealis rays above a silhouette of mountain peaks and a scrolling text ticker at the bottom of the screen.

---

## Hardware

- LilyGO T-PicoC3 ESP32 display board
- Small rechargeable LiPo battery (for portable power)
- USB C cable for testing

---

## Software / Dependencies

- PlatformIO
- TFT_eSPI library

---

## Installation

1. Install the **ESP32 board package** in the Arduino IDE.
2. Install the **TFT_eSPI** library.
3. Configure `TFT_eSPI` for your display (`User_Setup.h`).
4. Upload `main.cpp` to the ESP32.

---

## Usage

1. Plug the LilyGO T-PicoC3 into your computer using your USB-C cable.
2. Upload and run the program from PlatformIO:
```pio run --target upload```

Optionally, you can connect a small rechargeable LiPo battery to power the board for a limited time without the USB C cable.

![ESP32 display running the visuals](docs/esp_demo_0.jpg)

The scrolling text can be modified in the code at:

```cpp
String msg = "...";
