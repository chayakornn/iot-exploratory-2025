# ESP32 - IoT Exploratory 2025

This section contains examples for working with **ESP32** microcontroller.

```
📂 ESP32
│-- 📂 sensors
│   │-- Digital switch
│   │-- Potentiometer
│   │-- BH1750 Light sensor
│   │-- LTR390 Ultraviolet sensor
│   │-- RCWL-0516 Microwave radar sensor
│   │-- BME680 Air quality sensor
│   │-- Analog turbidity sensor
│   │-- MSP430FR2676 Capacitive touch sensor
│   │-- DHT11 Temperature and humidity sensor
│   │-- AO-03 ASAir Oxygen sensor
│   │-- MH-Z19C CO2 sensor
│   │-- GY-906-BCC Non-contact temperature sensor
│   │-- DS18B20 Liquid temperature sensor
│   │-- BMP280 Barometer sensor
│   │-- Flex sensor
│-- 📂 peripherals
│   │-- 4x4 matrix keypad
│   │-- 0.91-inch OLED display
│   │-- LED and Keypad module
│   │-- NFC MFRC-522 RFID card reader
│-- 📂 actuators
│   │-- 5V DC fan
│   │-- Buzzer module
│   │-- LED traffic light module
│   │-- Mist module
│   │-- Relay board
│-- 📜 README.md
```

## 📖 Table of Contents

### Sensors
- **Digital switch**

  Connect a push button to the IO pin of the microcontroller, e.g. at pin 4, then use the following code to read the button.

  ```cpp
  // Define the pin numbers
  const int buttonPin = 4;  // Pin where the button is connected
  const int ledPin =  2;    // Pin where the LED is connected
  
  // Variable to hold button state
  int buttonState = 0;       
  
  void setup() {
    // Initialize the LED pin as an output
    pinMode(ledPin, OUTPUT);
    // Initialize the button pin as an input
    pinMode(buttonPin, INPUT);
  }
  
  void loop() {
    // Read the state of the button
    buttonState = digitalRead(buttonPin);
  
    // Check if the button is pressed
    if (buttonState == HIGH) {
      // Turn the LED on if the button is pressed
      digitalWrite(ledPin, HIGH);
    } else {
      // Turn the LED off if the button is not pressed
      digitalWrite(ledPin, LOW);
    }
  }
  ```

- **Potentiometer**

  Connect a potentiometer to pin 34 then use the following code to read the potentiometer.
  
  ```cpp
  // Define the potentiometer pin
  const int potPin = 34;  // GPIO34 (analog input pin on ESP32)
  
  // Variable to store the potentiometer value
  int potValue = 0;
  
  void setup() {
    // Start serial communication
    Serial.begin(115200);
  
    // Set the potentiometer pin as an input
    pinMode(potPin, INPUT);
  }
  
  void loop() {
    // Read the potentiometer value (0 to 4095)
    potValue = analogRead(potPin);
  
    // Print the potentiometer value to the serial monitor
    Serial.print("Potentiometer Value: ");
    Serial.println(potValue);
  
    // Add a small delay before the next reading
    delay(500);
  }
  
  ```

- **BH1750 Light sensor**

  This example demonstrates how to read values from a **BH1750 Light Sensor** using an **ESP32** (30-pin version). The BH1750 communicates via **I2C**.
  
  #### Requirements:
  - You will need to install the **BH1750** library in the Arduino IDE. Go to **Sketch** → **Include Library** → **Manage Libraries**, then search for **BH1750** and install it.
  - The **I2C address** for the BH1750 is typically `0x23` (default).
  
  ```cpp
  #include <Wire.h>
  #include <BH1750.h>
  
  // Create an instance of the BH1750 sensor
  BH1750 lightSensor;
  
  void setup() {
    // Start the serial communication
    Serial.begin(115200);
  
    // Initialize I2C communication on default pins (SDA = GPIO21, SCL = GPIO22 on ESP32)
    Wire.begin();
  
    // Initialize the BH1750 sensor
    if (lightSensor.begin()) {
      Serial.println("BH1750 sensor initialized successfully.");
    } else {
      Serial.println("Error: Failed to initialize BH1750 sensor.");
      while (1);  // Stop further execution if sensor fails
    }
  }
  
  void loop() {
    // Read the light level in lux
    float lux = lightSensor.readLightLevel();
  
    // Print the light level to the serial monitor
    Serial.print("Light Level: ");
    Serial.print(lux);
    Serial.println(" lux");
  
    // Add a small delay before the next reading
    delay(1000);
  }
  

- LTR390 Ultraviolet sensor
- RCWL-0516 Microwave radar sensor
- BME680 Air quality sensor
- Analog turbidity sensor
- MSP430FR2676 Capacitive touch sensor
- DHT11 Temperature and humidity sensor
- AO-03 ASAir Oxygen sensor
- MH-Z19C CO2 sensor
- GY-906-BCC Non-contact temperature sensor
- DS18B20 Liquid temperature sensor
- BMP280 Barometer sensor
- Flex sensor

### Peripherals
- 4x4 Matrix Keypad
- 0.91-inch OLED display
- LED and Keypad module
- NFC MFRC-522 RFID card reader

### Actuators
- 5V DC fan
- Buzzer module
- LED traffic light module
- Mist module
- Relay board
