
Reaction Test Project
This project is a simple reaction test implemented on Arduino using an OLED display and RGB LEDs. It measures the time it takes for a user to press a button after a visual cue, and displays the reaction time on the OLED screen.

Components Used
- Arduino uno board (compatible with Adafruit libraries)
- OLED Display (Adafruit SSD1306)
- 3x LEDs (red,green,blue)
- Push Button

Upon starting the Arduino, the OLED display will show "Reaction Test" indicating the system is ready.
The system will then randomly choose a time between 3 to 7 seconds as the reaction time window. During this time, the red LED will be lit.
After the reaction time window, the green LED will turn on, indicating the user should press the action button as quickly as possible.
When the button is pressed, the blue LED will light up, and the reaction time will be displayed on the OLED screen in milliseconds.
The system then enters the end state, and the test can be restarted by resetting the Arduino.

LED Colors
Red: Indicates the start of the reaction time window.
Green: Indicates the user should press the button.
Blue: Indicates the reaction time measurement is in progress.
