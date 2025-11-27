# MULTIFUNCTION-ALARAM-CLOCK-WITH-ROOM-TEMPERATURE-DISPLAY
⏱️ Real-time clock with live date & weekday display.Continuously reads and displays the current time, date, and weekday on the LCD using an on-chip RTC for accurate timekeeping.
🌡️ Room temperature monitoring using LM35.Measures room temperature in real-time using the LM35 sensor through the ADC module and updates the display instantly.
🔔 Smart alarm with buzzer and auto/manual stop.Compares the current time with a user-configured alarm time and activates a buzzer when they match. The alarm can be stopped using a dedicated button or will automatically stop after one minute.
🚨 Interrupt-based menu for quick access.A dedicated switch triggers an external interrupt that pauses normal operation and provides the user with a configuration menu for easy system control.
🔢 Keypad control for easy user input.

✔️ Validated RTC & alarm settings for accuracy

📟 LCD interface for clear and user-friendly updates.LCD menu provides three choices:
1️⃣ Edit RTC Info
2️⃣ Set Alarm
3️⃣ Exit
allowing smooth navigation and feature access.

RTC Editing with Validation:
Users can modify hours, minutes, seconds, day, date, month, and year through the keypad. Each entry is validated for correct range considering leap years and month/day limits.
