# STM_Nucleo_RTC_Project_CSE211s
# Real-Time Clock and ADC Display System

**Course**: CSE211s - Introduction to Embedded Systems  
**Institution**: Ain Shams University - Faculty of Engineering  
**Department**: Mechatronics  
**Semester**: Spring 2025

## 📋 Project Overview

This embedded systems project uses the **NUCLEO-F401RE** board with an **Arduino Multifunction Shield** to implement two main functionalities:

- A **Real-Time Clock (RTC)** that displays elapsed time since system reset.
- A **voltage display** using the built-in potentiometer and on-chip ADC.

## 🚀 Features

### ⏱️ Real-Time Clock (RTC)
- Displays minutes and seconds on the 7-segment display.
- Starts counting from `00:00` upon board reset.
- Press **Switch S1** to reset the clock at any time.

### 🔧 Analog Voltage Display (ADC)
- Reads voltage from the on-board potentiometer.
- Press **Switch S3** to show the voltage value on the 7-segment display (in volts).
- Releasing **S3** returns to time display without interrupting the RTC.

## 🛠️ Hardware Components

- STM32 NUCLEO-F401RE Development Board (Cortex-M4)
- Arduino Multifunction Shield
  - 4-digit 7-segment display
  - Potentiometer
  - Switches (S1, S2, S3)

## 🧑‍💻 Software Requirements

- [Mbed Studio](https://os.mbed.com/studio/) or STM32CubeIDE
- STM32 NUCLEO board libraries and drivers

## 🎥 Demo Video

<p align="center">
  <a href="https://github.com/user-attachments/assets/04045425-ad11-4d25-978a-69b1cf61f7b9">
  <img src="https://github.com/user-attachments/assets/c8629a57-b736-4b60-bd98-f1bf99c9fff9" alt="Watch the video" width="600"/>
  </a>

</p>

## 📦 Getting Started

1. Clone this repository:
   ```bash
   git clone https://github.com/AdhamWaleedFayad/STM_Nucleo_RTC_Project_CSE211s.git

## 🧑‍💻 Contributers
- [@AdhamWaleedFayad](https://github.com/AdhamWaleedFayad)
- [@Marwanmahmoud02](https://github.com/Marwanmahmoud02)
- [@Omar61554](https://github.com/Omar61554)
