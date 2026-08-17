\# 🚗 Dual-Mode Robot Car System



<p align="center">

&#x20; <b>

&#x20;   A dual-mode robotic car system combining a Flutter mobile application, ESP32 embedded firmware, Bluetooth communication, and custom-designed PCB hardware.

&#x20; </b>

</p>



\---



\## 📌 Overview



The \*\*Dual-Mode Robot Car System\*\* is an embedded and mobile application project designed to demonstrate the integration of \*\*hardware, firmware, and mobile software\*\* into a complete robotic system.



The system supports two operating modes:



\- \*\*Manual Mode\*\* – The robot car is controlled remotely through a Flutter mobile application via Bluetooth.

\- \*\*Automatic Mode\*\* – The robot car performs autonomous control based on data from onboard sensors.



The project covers the complete development process, including PCB design, embedded firmware development, Bluetooth communication, mobile application development, hardware assembly, and system integration.

---

## ✨ Key Features



\- 📱 \*\*Mobile Control\*\* – Control the robot car through a Flutter mobile application.

\- 📡 \*\*Bluetooth Communication\*\* – Wireless communication between the mobile application and ESP32.

\- 🤖 \*\*Automatic Mode\*\* – Allow the robot to make movement decisions based on sensor data.

\- 🔌 \*\*Custom PCB\*\* – Hardware designed and developed specifically for the robot car.

\- 🧠 \*\*Embedded Firmware\*\* – Developed using ESP-IDF and FreeRTOS.

\- 🔄 \*\*System Integration\*\* – Integrating the mobile application, Bluetooth communication, firmware, and hardware into a complete system.


\---

## 🧠 What I Learned



\- ESP32 development with the ESP-IDF framework

\- Organizing and developing an ESP-IDF project

\- Bluetooth communication between mobile application and ESP32

\- Flutter mobile application development

\- PCB schematic and layout design with Altium Designer

\- Hardware assembly and soldering

\- Debugging hardware and firmware issues

\- Integrating hardware, firmware, and mobile software

\- Using Git and GitHub for project management

---

## 📝 Notes

> \*\*Project Status:\*\* 🟡 Paused — Approximately 90–95% complete

First, the project is approximately 90-95% complete. I mention this because the robot itself is not fully operational yet. After the debugging process, I identified two main issues:


- I cut the wires of the SG90 servo and connected them to male jumper wires. Therefore, the servo motor may have been damaged or may not operate properly.
- Although the power supply voltage is correct, the battery's discharge current is too low. Therefore, I believe that the motor driver and motors are not receiving enough power to operate properly.


Second, I built this project during my summer vacation to develop my programming and embedded systems skills. I decided to stop working on this project and focus on other projects during the next semester at university.


Finally, I believe that if these two issues are resolved, the robot should be able to operate smoothly.


Thanks for reading!

