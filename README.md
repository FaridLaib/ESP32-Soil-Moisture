# ESP32-Soil-Moisture
Measure the moisture of a soil using sensors


# Summary #

Hardware used:

Soil moisture sensor (analog input on GPIO 4)

128×64 OLED display using I²C (SDA = 21, SCL = 22)

Built-in LED (GPIO 2)

# Main Features #

Initialization:

Starts serial communication (115200 baud).

Initializes the OLED display with a title screen.

Sets up I²C and LED pins.

Sensor Reading (every 5 seconds):

Reads analog soil moisture data.

Converts raw sensor value into a percentage based on calibration (dryValue = 3000, wetValue = 1500).

Prints both raw and percentage values to the serial monitor.

# Display Output: #

Shows current soil moisture percentage on the OLED.

Displays a message if the value is below 40% (“Give me some water, please!”).

Indicates the ideal range (40–70%).

# LED Indicator: #

LED blinks every 5 seconds when moisture < 40%.

LED remains off when moisture is adequate.

# Purpose #

A simple soil-moisture monitoring system that provides both visual feedback (OLED + LED) and serial output, suitable for plant-watering reminders or basic IoT gardening projects.
