# Smart Parking System (Arduino Mega 2560)

An automated smart parking prototype developed as part of a student research paper for the **IEEESTEC** conference. The system monitors parking slot occupancy in real time, controls entry/exit gates, and displays available spaces to drivers.

## Key Features
- **Real-Time Slot Detection:** Ultrasonic distance sensors detect vehicle presence in individual parking spaces.
- **Automated Gate Control:** Dual servo motors operate entry and exit barriers triggered by vehicle detection and push-button input.
- **Visual Status Indicators:** RGB LEDs indicate whether each parking spot is free (green) or occupied (red).
- **User Interface:** A 16x2 LCD screen displays the current number of available parking slots and system status messages.

## Hardware Components
- **Microcontroller:** Arduino Mega 2560
- **Sensors:** Ultrasonic distance sensors, push button
- **Actuators & Indicators:** Servo motors, RGB LEDs, 16x2 LCD display

## Repository Contents
- `projekat1.ino` – Complete Arduino firmware written in C/C++
- `Pametan parking IEEESTEC.doc` – Full conference paper detailing system architecture, hardware wiring, and implementation
