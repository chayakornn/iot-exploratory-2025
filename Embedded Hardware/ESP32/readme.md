# ESP32 - IoT Exploratory 2025

## Introduction to ESP32

The **ESP32** is a powerful, low-cost microcontroller with built-in **Wi-Fi** and **Bluetooth**, making it ideal for IoT applications. It features multiple **GPIOs**, **analog inputs**, and **digital interfaces** like **I2C, SPI, and UART**. With robust processing capabilities and low power consumption, ESP32 is widely used for **sensor data collection, automation, and real-time communication** in IoT projects.

In this workshop, we will explore ESP32’s capabilities through **hands-on examples** covering **sensors, peripherals, and actuators** to build smart IoT solutions. 🚀

## ESP32 Pinout Diagram

Here is the pinout diagram for the **ESP32 DevKit V1 (30-pin version):**

![ESP32 Pinout](https://lastminuteengineers.com/wp-content/uploads/iot/ESP32-Pinout.png)
*Image Source: [https://lastminuteengineers.com](https://lastminuteengineers.com)*

## Sensors, Peripherals and Actuators

This section covers some **hardware components** used with ESP32 in this workshop, including **sensors** for data collection, **peripherals** for interfacing, and **actuators** for controlling external devices. These components form the backbone of IoT applications, enabling interaction with the physical world.  

Explore the examples to learn how to **read sensor data, display information, and control actuators** using ESP32! 🚀  

```
📂 ESP32
│-- 📂 [Sensors](#sensors)
│   │-- Digital switch
│   │-- Potentiometer
│   │-- BH1750 Light sensor
│   │-- RCWL-0516 Microwave radar sensor
│   │-- DHT11 Temperature and humidity sensor
│-- 📂 peripherals
│   │-- 4x4 matrix keypad
│   │-- 0.91-inch OLED display
│   │-- LED and Keypad module
│   │-- NFC MFRC-522 RFID card reader
│-- 📂 actuators
│   │-- 5V DC fan
│   │-- Buzzer module
│   │-- LED traffic light module
│   │-- Relay board
│-- 📂 [Extra](#extra)
│   │-- LTR390 Ultraviolet sensor
│   │-- BME680 Air quality sensor
│   │-- Analog turbidity sensor
│   │-- MSP430FR2676 Capacitive touch sensor
│   │-- AO-03 ASAir Oxygen sensor
│   │-- MH-Z19C CO2 sensor
│   │-- GY-906-BCC Non-contact temperature sensor
│   │-- DS18B20 Liquid temperature sensor
│   │-- BMP280 Barometer sensor
│   │-- Flex sensor
│   │-- Mist module
│-- 📜 README.md
```
---
## 📖 Table of Contents
- [**Sensors**](#sensors)
  - [Digital Switch](#digital-switch)
  - [Potentiometer](#potentiometer)
  - [BH1750 Light Sensor](#bh1750-light-sensor)
  - [RCWL-0516 Microwave Radar Sensor](#rcwl-0516-microwave-radar-sensor)
  - [DHT11 Temperature and humidity sensor](#dht11-temperature-and-humidity-sensor)
- [**Peripherals**](#peripherals)
  - [4x4 Matrix Keypad](#4x4-matrix-keypad)
  - [0.91-inch OLED Display](#oled-display)
  - LED and Keypad Module
- [**Actuators**](#actuators)
  - 5V DC Fan
  - Buzzer Module
  - LED Traffic Light Module
- [**Extra**](#extra)
  - [LTR390 Ultraviolet sensor](#ltr390-ultraviolet-sensor)

---
### Sensors
**Sensors** are devices that detect changes in the environment and convert them into electrical signals that can be processed by a microcontroller or computer. In the context of IoT, sensors play a crucial role in collecting data from the physical world, such as temperature, humidity, motion, light, and more. By integrating sensors into IoT projects, we can gather real-time data and make intelligent decisions based on that information.

---
#### Digital Switch  

  <img src="https://i.lnwfile.com/_/i/_raw/eq/f0/3c.jpg" alt="Push Button" width="350">
  
  *Image Source: [[Arduino All](https://arduinoall.com)]*  

  A **digital switch (push button)** allows the ESP32 to detect user input and trigger actions based on its state. This type of button has **three pins**:  

  - **V (Voltage)** → Connects to **3.3V or 5V**  
  - **G (Ground)** → Connects to **GND**  
  - **S (Signal)** → Connects to a **GPIO pin** (e.g., GPIO 4)  

  **🛠 Wiring:**  
  - **V** → **3.3V (ESP32)**  
  - **G** → **GND**  
  - **S** → **GPIO 4**  

  **📜 Example Code:**  

  ```cpp
  const int buttonPin = 4;  // Define the GPIO pin
  int buttonState = 0;  

  void setup() {
      pinMode(buttonPin, INPUT);  // Set button pin as input
      Serial.begin(115200);
  }

  void loop() {
      buttonState = digitalRead(buttonPin);  // Read button state
      Serial.println(buttonState ? "Button Released" : "Button Pressed");
      delay(100);
  }
```
---
#### Potentiometer

  <img src="https://electricityforum.com/uploads/articles/potentiometer2_1496554845.webp" alt="Potentiometer" width="350">

  *Image Source: [[https://electricityforum.com](https://electricityforum.com/what-is-a-potentiometer)]*  
  
  A **potentiometer** (variable resistor) commonly used for adjusting brightness, volume, or other input values. It outputs a variable voltage between **0V and 3.3V**, which the ESP32 reads using its **ADC (Analog-to-Digital Converter)**.  

  **🛠 Wiring:**  
  - **VCC (Left pin)** → **3.3V**  
  - **GND (Right pin)** → **GND**  
  - **Output (Middle pin)** → **GPIO 34**  

  **📜 Example Code:**  

  ```cpp
  const int potPin = 34;  // Potentiometer connected to GPIO 34
  int potValue = 0;       // Variable to store ADC reading

  void setup() {
      Serial.begin(115200);
  }

  void loop() {
      potValue = analogRead(potPin);  // Read analog value (0-4095)
      Serial.print("Potentiometer Value: ");
      Serial.println(potValue);
      delay(100);
  }
```
---
#### BH1750 Light Sensor

  <img src="https://esphome.io/_images/bh1750-full.jpg" alt="BH1750" width="350">

  *Image Source: [[https://esphome.io](https://esphome.io/components/sensor/bh1750.html)]*  

  The **BH1750** is a digital ambient light sensor that measures **illuminance (lux)** using an **I2C interface**. It is useful for **automatic brightness adjustment, smart lighting, and environmental monitoring**. The ESP32 reads the sensor data via **GPIO 21 (SDA) and GPIO 22 (SCL)**.  

  **🛠 Wiring:**  
  - **VCC** → **3.3V** (or **5V**, depending on module)  
  - **GND** → **GND**  
  - **SDA** → **GPIO 21**  
  - **SCL** → **GPIO 22**  

  **📥 Library Installation:**  
  Before running the code, install the **BH1750** library:  
  1. Open **Arduino IDE**.  
  2. Go to **Sketch** → **Include Library** → **Manage Libraries**.  
  3. Search for **BH1750** by Christopher Laws, select it, and click **Install**.  

  **📜 Example Code:**  

  ```cpp
  #include <Wire.h>
  #include <BH1750.h>

  BH1750 lightSensor;

  void setup() {
      Serial.begin(115200);
      Wire.begin();  // Initialize I2C (SDA=GPIO21, SCL=GPIO22)

      if (lightSensor.begin()) {
          Serial.println("BH1750 sensor initialized successfully.");
      } else {
          Serial.println("Error: Failed to initialize BH1750 sensor.");
          while (1);  // Stop execution if sensor fails
      }
  }

  void loop() {
      float lux = lightSensor.readLightLevel();  // Read light level

      Serial.print("Light Level: ");
      Serial.print(lux);
      Serial.println(" lux");

      delay(1000);  // Read every second
  }
```
---
#### RCWL-0516 Microwave Radar Sensor

  <img src="https://static.cytron.io/image/cache/catalog/products/SN-RCWL-0516/SN-RCWL-0516-800x800.jpg" alt="RCWL-0516 Microwave Radar Sensor" width="350">

  *Image Source: [[https://static.cytron.io](https://static.cytron.io/image/cache/catalog/products/SN-RCWL-0516/SN-RCWL-0516-800x800.jpg)]*  

  The **RCWL-0516** is a **microwave motion sensor** that detects movement using **Doppler radar technology** rather than infrared. Unlike PIR sensors, it can detect motion through **walls, glass, and plastic**, making it ideal for **security systems, automation, and smart lighting**.  

  **🛠 Wiring:**  
  - **VIN** → **3.3V or 5V**  
  - **GND** → **GND**  
  - **OUT** → **GPIO 4** (or any digital pin)  

  **📜 Example Code:**  

  ```cpp
  const int sensorPin = 4;  // RCWL-0516 OUT pin connected to GPIO 4
  int motionState = 0;  

  void setup() {
      pinMode(sensorPin, INPUT);
      Serial.begin(115200);
  }

  void loop() {
      motionState = digitalRead(sensorPin);  // Read motion sensor output

      if (motionState == HIGH) {
          Serial.println("Motion detected!");
      } else {
          Serial.println("No motion.");
      }
      
      delay(500);  // Adjust delay as needed
  }
```
---
#### DHT11 temperature and humidity sensor

  <img src="https://components101.com/sites/default/files/components/DHT11-Sensor.jpg" alt="DHT11" width="350"/>

  *Image Source: [[https://components101.com](https://components101.com/sites/default/files/components/DHT11-Sensor.jpg)]*  

  The **DHT11** is a popular **temperature and humidity sensor** that provides digital output via a single data pin. It is commonly used in **weather stations, home automation, and environmental monitoring**.  

  **🛠 Wiring:**  
  - **VCC** → **3.3V or 5V** (ESP32 supports both)  
  - **GND** → **GND**  
  - **DATA** → **GPIO 2** (or any digital pin)  
  - (Optional) **10kΩ pull-up resistor** between **DATA** and **VCC**  

  **📜 Example Code:**  

  ```cpp
  // Include the DHT11 library for interfacing with the sensor.
  #include <DHT11.h>

  // Create an instance of the DHT11 class.
  // - For ESP32: Connect the sensor to pin GPIO2.
  DHT11 dht11(2);

  void setup() {
      // Initialize serial communication for debugging and data readout.
      Serial.begin(9600);
      
      // Uncomment the line below to set a custom delay between sensor readings (in milliseconds).
      // dht11.setDelay(500); // Default delay is 500ms.
  }

  void loop() {
      int temperature = 0;
      int humidity = 0;

      // Read temperature and humidity values from the DHT11 sensor.
      int result = dht11.readTemperatureHumidity(temperature, humidity);

      // Check if the reading is successful.
      if (result == 0) {
          Serial.print("Temperature: ");
          Serial.print(temperature);
          Serial.print(" °C\tHumidity: ");
          Serial.print(humidity);
          Serial.println(" %");
      } else {
          // Print an error message if the reading fails.
          Serial.println(DHT11::getErrorString(result));
      }
  }
```
---
### LTR390 Ultraviolet Sensor

<img src="https://static.cytron.io/image/cache/catalog/products/SN-LTR390-UV01/UV-Sensor-C-details-1-800x800.jpeg" alt="LTR390 UV Sensor" width="350"/>  

Image Source: [[Cytron](https://th.cytron.io/p-digital-ltr390-ultraviolet-uv-sensor?r=1&language=en-gb&gad_source=1&gclid=Cj0KCQjwtJ6_BhDWARIsAGanmKcKcjH1q0FQvHI0SktUjRc4RY_cX3QgSDuyfTgwjSHe_8Vej9zLlgAaAqh2EALw_wcB)]

The **LTR390** is a **UV and ambient light sensor** that communicates using the **I2C protocol**. It is useful for detecting **UV radiation levels** in applications such as environmental monitoring, UV index measurement, and smart wearables.  

**🛠 Wiring (ESP32 - LTR390)**  

| **LTR390 Pin** | **ESP32 Pin** |
|--------------|--------------|
| VCC         | 3.3V         |
| GND         | GND          |
| SDA         | GPIO 21 (SDA) |
| SCL         | GPIO 22 (SCL) |


**📜 Example Code**  

```cpp
#include <Wire.h>
#include <Adafruit_LTR390.h>

Adafruit_LTR390 ltr = Adafruit_LTR390();

void setup() {
    Serial.begin(115200);
    Wire.begin(); // Initialize I2C

    if (!ltr.begin()) {
        Serial.println("Error: LTR390 sensor not found. Check wiring!");
        while (1); // Halt execution
    }

    Serial.println("LTR390 sensor initialized!");
    ltr.setMode(LTR390_MODE_UVS); // Set to UVS mode
    ltr.setGain(LTR390_GAIN_3);   // Set gain
    ltr.setResolution(LTR390_RESOLUTION_16BIT); // Set resolution
}

void loop() {
    if (ltr.newDataAvailable()) {
        uint32_t uvData = ltr.readUVS();
        Serial.print("UV Light Level: ");
        Serial.println(uvData);
    } else {
        Serial.println("No new UV data available.");
    }

    delay(1000);
}
```

- BME680 Air quality sensor
- Analog turbidity sensor
- MSP430FR2676 Capacitive touch sensor
- AO-03 ASAir Oxygen sensor
- MH-Z19C CO2 sensor
- GY-906-BCC Non-contact temperature sensor
- DS18B20 Liquid temperature sensor
- BMP280 Barometer sensor
- Flex sensor

---
### Peripherals

### 4x4 Matrix Keypad

<img src="https://www.circuitbasics.com/wp-content/uploads/2017/07/Arduino-Keypad-Tutorial-4X4-and-3X4-Keypad-Pin-Diagram-768x730.png" alt="4x4 matrix keypad" width="350"/>  

Image Source: [[Circuitbasics](https://www.circuitbasics.com/wp-content/uploads/2017/07/Arduino-Keypad-Tutorial-4X4-and-3X4-Keypad-Pin-Diagram-768x730.png)]

The **4x4 Matrix Keypad** is a commonly used input device in IoT projects. It features 16 buttons organized in a 4x4 grid, providing a simple interface for user input, such as entering numbers or performing tasks based on keypresses.

**🛠 Wiring (To ESP32)**
| Keypad Pin | ESP32 Pin |
|------------|-----------|
| R1         | GPIO 13   |
| R2         | GPIO 12   |
| R3         | GPIO 14   |
| R4         | GPIO 27   |
| C1         | GPIO 26   |
| C2         | GPIO 25   |
| C3         | GPIO 33   |
| C4         | GPIO 32   |

**📜 Example Code**
To interface with the keypad, you'll need the **Keypad** library. Install it via the Arduino Library Manager (`Sketch` → `Include Library` → `Manage Libraries...`), then search for **Keypad** by Community https://github.com/Christ--A/Keypad.

```cpp
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {13, 12, 14, 27}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {26, 25, 33, 32}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

void setup(){
  Serial.begin(115200);
}
  
void loop(){
  char customKey = customKeypad.getKey();
  
  if (customKey){
    Serial.println(customKey);
  }
}
```
---

### OLED Display

<img src="https://www.elementzonline.com/image/cache/catalog/data/products/DISPLAY/OLED%20/OLED%200.91%20inch/OLED-0-91-inch-Display-main-550x550w.jpg" alt="0.91-inch OLED Display" width="350">

Image Source: [[elementzonline](https://www.elementzonline.com/oled-display-board-0-91-inch-128x32-ssd1306-i2c-iic-serial-4-pin-module)]

The **0.91-inch OLED display** (SSD1306) is a **monochrome, low-power display** that communicates with the ESP32 using **I2C** or **SPI**. It is ideal for displaying sensor data, system status, and graphical elements in IoT applications.

**🛠 Wiring (I2C Mode - Default)**
| OLED Pin | ESP32 Pin |
|----------|----------|
| VCC      | 3.3V     |
| GND      | GND      |
| SDA      | GPIO21   |
| SCL      | GPIO22   |

**📜 Example Code (I2C)**
```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C  // I2C address of the display

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
    Serial.begin(115200);
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;);
    }
    display.clearDisplay();
    
    // Display text
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 10);
    display.println("Hello, OLED!");
    display.display();
}

void loop() {
}
```


- LED and Keypad module

---
### MFRC522 RFID card reader


<img src="https://raw.githubusercontent.com/playfultechnology/arduino-rfid-MFRC522/master/documentation/MFRC522.jpg" alt="MFRC522 RFID card reader" width="350">

Image Source: [[github/playfultechnology](https://raw.githubusercontent.com/playfultechnology/arduino-rfid-MFRC522/master/documentation/MFRC522.jpg)]

The **MFRC522** module is an RFID (Radio Frequency Identification) reader that communicates with a microcontroller via **SPI**. It is commonly used in access control systems, ticketing, and IoT projects requiring identification or authentication.

**🛠 Wiring (To ESP32)**
| MFRC522 Pin | ESP32 Pin |
|-------------|-----------|
| SDA         | GPIO 5    |
| SCK         | GPIO 18   |
| MOSI        | GPIO 23   |
| MISO        | GPIO 19   |
| IRQ         |  -        |
| GND         | GND      |
| RST         | GPIO 22   |
| 3.3V        | 3.3V     |

#### 📜 Example Code
To interface with the **MFRC522** module, you will need the **MFRC522** library. Install it via the Arduino Library Manager (`Sketch` → `Include Library` → `Manage Libraries...`), then search for **MFRC522** by githubcommunity.

```cpp
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5    // Slave Select pin
#define RST_PIN 22  // Reset pin

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

void setup() {
  Serial.begin(115200);  // Initialize serial communication
  SPI.begin();  // Initialize SPI bus
  mfrc522.PCD_Init();  // Initialize MFRC522 reader

  Serial.println("Place an RFID card or tag near the reader.");
}

void loop() {
  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent()) {
    // Select one of the cards
    if (mfrc522.PICC_ReadCardSerial()) {
      Serial.print("UID tag :");
      
      // Read the UID of the card
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
        Serial.print(mfrc522.uid.uidByte[i], HEX);
      }
      Serial.println();

      mfrc522.PICC_HaltA();  // Halt the PICC (RFID card)
    }
  }
}


### Actuators
- 5V DC fan
- Buzzer module
- LED traffic light module
- Mist module
- Relay board
