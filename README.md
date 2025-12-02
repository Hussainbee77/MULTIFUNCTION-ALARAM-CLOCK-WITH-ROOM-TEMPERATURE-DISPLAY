# MULTIFUNCTION-ALARAM-CLOCK-WITH-ROOM-TEMPERATURE-DISPLAY

🔹 Project Overview

A real-time embedded system built using LPC2148 ARM7 microcontroller, featuring live clock display, temperature monitoring, user-configurable alarm, and easy interaction through a keypad and LCD interface.

---

🚀 Key Features

⌚ Accurate Real-Time Clock (RTC)
Continuously displays current time, date, and weekday with precise timekeeping using the onboard RTC.

🌡️ Live Temperature Monitoring
Measures room temperature in real-time using LM35 sensor via ADC and updates the LCD instantly.

🔔 Smart Alarm System
User-configurable alarm using keypad input
Alarm triggers a buzzer when time matches
Auto-stop after 1 minute & manual stop supported
Reliable daily reminder functionality

🔢 Easy Keypad Interface
4×4 matrix keypad enables
RTC editing
Alarm setting
Menu navigation
Input values are validated for accuracy.


📟 User-Friendly LCD Display
Character LCD provides clear display of
Time, date, temperature
Menu options and user prompts
Error messages for invalid inputs

🚨 Interrupt-Driven Quick Access Menu
External interrupt triggers a direct jump to the configuration menu without interrupting system performance.

✔️ RTC Editing with Input Validation
Ensures valid ranges for time/date including leap year handling before updating RTC registers.
---

🛠️ Development Workflow

Keil µVision4 IDE
Full embedded C code development
Error detection, step-wise debugging, peripheral simulation
Generates HEX file for final flashing
Ensures reliable and accurate firmware behavior
Flash Magic for Programming
Loads HEX file into LPC2148 via ISP and UART0
Performs flash erase, write & verification
Runs the embedded application in real hardware
UART0 for Debugging
Transfers real-time logs to PC terminal
Assists in testing without relying fully on LCD display

🔌 Power Supply Integration

Provides regulated 3.3V and 5V DC
3.3V for LPC2148 core and peripherals
5V for LCD, keypad, LM35 & RTC modules
Common ground ensures noise-free stable operation
On-board regulator converts 5V → 3.3V for safe MCU usage

📍 Project Highlights

✔ Real-time monitoring and standalone operation
✔ Interrupt-based fast configuration
✔ Fully validated user inputs for high accuracy
✔ Embedded debugging support for system testing
✔ Efficient communication using UART0.
