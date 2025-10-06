#include <Wire.h>
#include <U8g2lib.h>

#define I2C_SDA 21
#define I2C_SCL 22

#define SOIL_MOISTURE_PIN 4  // Pin connected to the soil moisture sensor
#define BUILTIN_LED 2        // Pin for the built-in LED (often GPIO 2)

// Initialize U8G2 for the OLED display
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, I2C_SDA, I2C_SCL);  // 128x64 OLED with hardware I2C

// Calibration values (replace these with your sensor's dry and wet values)
int dryValue = 3000;  // Replace with your dry calibration value
int wetValue = 1500;  // Replace with your wet calibration value

unsigned long previousMillis = 0;     // Store the last time for LED toggling
const long ledInterval = 5000;        // Interval for LED blinking (ms)
unsigned long sensorMillis = 0;       // Store the last time for sensor reading
const long sensorInterval = 5000;     // Interval for sensor updates (ms)

int moisturePercentage = 0;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200);
  delay(1500); // Allow time for the Serial Monitor to open

  // Set the built-in LED pin as output
  pinMode(BUILTIN_LED, OUTPUT);

  // Initialize I2C communication
  Wire.begin(I2C_SDA, I2C_SCL);

  // Initialize the OLED display
  u8g2.begin();

  // Initial display message
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);  // Simple font
  u8g2.setCursor(0, 10);
  u8g2.print("Soil Moisture Sensor");
  u8g2.sendBuffer();
  delay(2000);
}

void loop() {
  unsigned long currentMillis = millis();

  // Read and update sensor values every 2 seconds
  if (currentMillis - sensorMillis >= sensorInterval) {
    sensorMillis = currentMillis;

    // Read raw value from soil moisture sensor
    int rawValue = analogRead(SOIL_MOISTURE_PIN);

    // Map raw value to percentage
    moisturePercentage = map(rawValue, dryValue, wetValue, 0, 100);
    moisturePercentage = constrain(moisturePercentage, 0, 100);

    // Print values to Serial Monitor
    Serial.print("Raw Value: ");
    Serial.print(rawValue);
    Serial.print(" | Moisture: ");
    Serial.print(moisturePercentage);
    Serial.println("%");

    // Update OLED display
    u8g2.clearBuffer();
    u8g2.setFont(u8g2_font_ncenB08_tr);
    u8g2.setCursor(0, 10);
    u8g2.print("General Moisture: ");
    u8g2.print(moisturePercentage);
    u8g2.print("%");

    u8g2.setCursor(0, 25);
    u8g2.print("Ideal: 40%-70%");

    if (moisturePercentage < 40) {
      u8g2.setCursor(0, 40);
      u8g2.print("Give me some water, please!");
    }
    u8g2.sendBuffer();
  }

  // Blink LED if moisture is below 40%
  if (moisturePercentage < 40) {
    if (currentMillis - previousMillis >= ledInterval) {
      previousMillis = currentMillis;
      digitalWrite(BUILTIN_LED, !digitalRead(BUILTIN_LED)); // Toggle LED
    }
  } else {
    digitalWrite(BUILTIN_LED, LOW); // Ensure LED is off if moisture is sufficient
  }
}
