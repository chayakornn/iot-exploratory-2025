# ESP32 - IoT Exploratory 2025

## Introduction to ESP32

The **ESP32** is a powerful, low-cost microcontroller with built-in **Wi-Fi** and **Bluetooth**, making it ideal for IoT applications. It features multiple **GPIOs**, **analog inputs**, and **digital interfaces** like **I2C, SPI, and UART**. With robust processing capabilities and low power consumption, ESP32 is widely used for **sensor data collection, automation, and real-time communication** in IoT projects.

In this workshop, we will explore ESP32’s capabilities through **hands-on examples** covering **sensors, peripherals, and actuators** to build smart IoT solutions. 🚀

## ESP32 Pinout Diagram

Here is the pinout diagram for the **ESP32 DevKit V1 (30-pin version):**

![ESP32 Pinout](https://lastminuteengineers.com/wp-content/uploads/iot/ESP32-Pinout.png)

*Image Source: [https://lastminuteengineers.com](https://lastminuteengineers.com)*

*Note: The on-board LED is at pin GPIO2*

## Sensors, Peripherals and Actuators

This section covers some **hardware components** used with ESP32 in this workshop, including **sensors** for data collection, **peripherals** for interfacing, and **actuators** for controlling external devices. These components form the backbone of IoT applications, enabling interaction with the physical world.  

Explore the examples to learn how to **read sensor data, display information, and control actuators** using ESP32! 🚀  

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
  - [MFRC522 RFID card reader](#mfrc522-rfid-card-reader)
- [**Actuators**](#actuators)
  - [Active Buzzer Module](#active-buzzer)
  - [LED Traffic Light Module](#led-traffic-light-module)
  - [Relay module](#relay-module)
  - [5V DC Fan](#5v-dc-fan)
  - [5V Humidifier](#5v-humidifier)
- [**Extra**](#extra)
  - [TM1638 LED and Key Module](#tm1638-led-and-key-module)
  - [LTR390 Ultraviolet sensor](#ltr390-ultraviolet-sensor)
  - [BME680 Air Quality, Temperature, Pressure, and Humidity Sensor](#bme680-air-quality-temperature-pressure-and-humidity-sensor)
  - [Analog turbidity sensor](#analog-turbidity-sensor)
  - [AO-03 ASAir Oxygen sensor](./O2_Sensor)
  - [MH-Z19C CO2 sensor](./CO2_Sensor)
  - [GY-906-BCC Non-contact temperature sensor](./GY906_Temperature_Sensor)
  - [MSP430FR2676 Capacitive touch sensor](https://th.rs-online.com/web/p/sensor-development-tools/2659748)
  - [DS18B20 Liquid temperature sensor](https://wiki.dfrobot.com/Waterproof_DS18B20_Digital_Temperature_Sensor__SKU_DFR0198_)
- [**MQTT for ESP32**](#mqtt-for-esp32)
  - [Wi-Fi Access Point Setup](#wi-fi-access-point-setup)
  - [Publish to a Single Topic](#publish-to-a-single-topic)
  - [Publish to Several Topics](#publish-to-several-topics)
  - [Subscribe to a Single Topic](#subscribe-to-a-single-topic)
  - [Subscribe to Several Topics](#subscribe-to-several-topics)
  - [Publish as JSON to MQTT](#publish-as-json_object-to-mqtt)
- [**I2C Communication**](#i2c-communication)
- [**End Device: Environmental Measurement System**](#end-device-environmental-measurement-system)

  
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
### Peripherals
Peripherals expand the ESP32’s capabilities by providing input and output interfaces. Devices like keypads, OLED displays, and RFID readers allow users to interact with the system, display information, and read data from external sources.

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
```

### Actuators
Actuators enable the ESP32 to control physical devices. Components like buzzers, relays, and fans allow automation, sound generation, and switching of high-power devices, making them essential for interactive and smart applications.

---
### 🔊 Active Buzzer

<img src="https://www.botnroll.com/10428-medium_default/active-buzzer-3-5-5-5vdc-for-funduino.jpg" alt="Active buzzer" width="350">

Image Source: [[botnroll](https://www.botnroll.com/10428-medium_default/active-buzzer-3-5-5-5vdc-for-funduino.jpg)]

The **3-pin active buzzer** is a simple sound-generating module that can produce tones when powered. Unlike a passive buzzer, which requires frequency control, an active buzzer generates sound with just a **HIGH** signal.

**🛠 Wiring (To ESP32)**
| Buzzer Pin | ESP32 Pin |
|------------|-----------|
| **SIG**    | GPIO 25   |
| **VCC**    | 3.3V      |
| **GND**    | GND       |


**📜 Example Code**
The following example demonstrates how to control the buzzer with an ESP32. The buzzer will beep on and off at 1-second intervals.

```cpp
const int buzzerPin = 25;  // Define the GPIO pin connected to the buzzer

void setup() {
  pinMode(buzzerPin, OUTPUT);  // Set the buzzer pin as an output
}

void loop() {
  digitalWrite(buzzerPin, HIGH);  // Turn the buzzer ON
  delay(1000);  // Wait for 1 second
  digitalWrite(buzzerPin, LOW);  // Turn the buzzer OFF
  delay(1000);  // Wait for 1 second
}
```

---

### 🚦 LED Traffic Light Module

<img src="https://dm.lnwfile.com/_/dm/_raw/yv/l1/qm.jpg" alt="LED traffic light module" width="350">

Image Source: [[genlogic](https://dm.lnwfile.com/_/dm/_raw/yv/l1/qm.jpg)]

The **LED Traffic Light Module** simulates a standard traffic light with three LEDs (**Red, Yellow, and Green**). It can be used to demonstrate traffic light sequences or other signaling applications.

**🛠 Wiring (To ESP32)**
| Module Pin | ESP32 Pin  | Function |
|------------|-----------|----------|
| **G**      | GPIO 12   | Green LED Control |
| **Y**      | GPIO 13   | Yellow LED Control |
| **R**      | GPIO 14   | Red LED Control |
| **GND**    | GND       | Ground |

**📜 Example Code**
This example simulates a basic traffic light cycle.

```cpp
const int greenLED = 12;   // Green LED pin
const int yellowLED = 13;  // Yellow LED pin
const int redLED = 14;     // Red LED pin

void setup() {
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
}

void loop() {
  digitalWrite(greenLED, HIGH);  // Green light ON
  delay(5000);                   // Wait 5 seconds
  digitalWrite(greenLED, LOW);

  digitalWrite(yellowLED, HIGH);  // Yellow light ON
  delay(2000);                    // Wait 2 seconds
  digitalWrite(yellowLED, LOW);

  digitalWrite(redLED, HIGH);     // Red light ON
  delay(5000);                    // Wait 5 seconds
  digitalWrite(redLED, LOW);
}
```

---

### ⚡ Relay Module

<img src="https://m.media-amazon.com/images/I/61blaLDLOzL._SX522_.jpg" alt="Relay  module" width="350">

Image Source: [[Amazon](https://m.media-amazon.com/images/I/61blaLDLOzL._SX522_.jpg)]

A **relay module** allows an ESP32 to control high-power electrical devices like lamps, fans, or appliances using a low-power signal. It acts as an electrically operated switch.

#### 🔹 How It Works
- When the **IN** pin is set **HIGH**, the relay **activates**, connecting **COM** to **NO**.
- When the **IN** pin is set **LOW**, the relay **deactivates**, connecting **COM** to **NC**.
- **NC (Normally Closed)** → Default **closed** circuit; current flows when the relay is **OFF**.
- **NO (Normally Open)** → Default **open** circuit; current flows when the relay is **ON**.

### 🛠 Relay Module Variants
#### **1-Channel Relay Module**
- **Input side (low voltage control):** `VCC`, `GND`, `IN`
- **Output side (high voltage switching):** `GND`, `NC`, `NO`

#### **2-Channel Relay Module**
- **Input side (low voltage control):** `VCC`, `GND`, `IN1`, `IN2`
- **Output side (high voltage switching):** Two sets of `GND`, `NC`, `NO` for each relay.

---

**🛠 Wiring (To ESP32)**
| Relay Pin | ESP32 Pin  | Function |
|-----------|-----------|----------|
| **VCC**   | 3.3V      | Power Supply |
| **GND**   | GND       | Ground |
| **IN** *(1-Channel)*  | GPIO 26 | Control Signal |
| **IN1** *(2-Channel)* | GPIO 26 | Control Relay 1 |
| **IN2** *(2-Channel)* | GPIO 27 | Control Relay 2 |

---

**📜 Example Code (1-Channel)**
```cpp
const int relayPin = 26;  // Relay control pin

void setup() {
  pinMode(relayPin, OUTPUT);
}

void loop() {
  digitalWrite(relayPin, HIGH);  // Turn relay ON
  delay(5000);                   // Keep it ON for 5 sec
  digitalWrite(relayPin, LOW);   // Turn relay OFF
  delay(5000);                   // Keep it OFF for 5 sec
}
```

---
### 🌬️ 5V DC Fan

<img src="https://static.cytron.io/image/cache/catalog/products/FAN-0305-3008/FAN-0305-3008_b-800x800.jpg" alt="5V DC fan" width="350">

Image Source: [[Cytron](https://static.cytron.io/image/cache/catalog/products/FAN-0305-3008/FAN-0305-3008_b-800x800.jpg)]

A **5V DC fan** is often used for cooling purposes in electronic projects. It's essential to note that you should **never directly drive the fan with an ESP32 GPIO pin**, as the GPIOs cannot supply enough current to safely power the fan. Instead, use a **relay module** or **transistor** as an intermediary to control the fan's operation.

---

**🛠 Wiring (To ESP32 via Relay Module)**
| Fan Pin | Connection      | Function                         |
|---------|-----------------|----------------------------------|
| **VCC** | 5V Power Supply | Provides power to the fan       |
| **GND** | ESP32 GND       | Common ground                   |
| **Relay NO** | Relay Output Pin | Connects to the fan's power     |
| **Relay IN** | GPIO Pin (e.g., GPIO 26) | Controls the relay and fan    |

🔹 **Important Notes:**
- Use the **Relay Module** to control the fan's power by switching its 5V supply.
- **Relay NO** (Normally Open) pin is used to connect the fan’s **VCC** to the 5V supply when the relay is activated.
  
---

**📜 Example Code**
```cpp
const int relayPin = 26;  // GPIO connected to relay module

void setup() {
  pinMode(relayPin, OUTPUT);  // Set relay pin as output
}

void loop() {
  digitalWrite(relayPin, HIGH);  // Turn fan ON by activating relay
  delay(5000);                   // Keep it ON for 5 sec
  digitalWrite(relayPin, LOW);   // Turn fan OFF by deactivating relay
  delay(5000);                   // Keep it OFF for 5 sec
}
```

---

### 💧 5V Humidifier

<img src="https://down-th.img.susercontent.com/file/th-11134207-7r98x-lpgg8tkc3zi695.webp" alt="5V humidifier" width="350">

Image Source: [[Shopee](https://down-th.img.susercontent.com/file/th-11134207-7r98x-lpgg8tkc3zi695.webp)]

A **5V humidifier** is often used to add moisture to the air, which is helpful in various IoT applications, especially those involving environmental control. Like other high-power devices, the humidifier should not be directly controlled by an **ESP32 GPIO pin**, as it does not provide sufficient current. Instead, you should use a **relay module** or a **transistor** to control the humidifier.

---

**🛠 Wiring (To ESP32 via Relay Module)**
| Humidifier Pin | Connection              | Function                         |
|----------------|-------------------------|----------------------------------|
| **VCC**        | 5V Power Supply         | Provides power to the humidifier |
| **GND**        | ESP32 GND               | Common ground                   |
| **Relay NO**   | Relay Output Pin        | Connects to the humidifier's power |
| **Relay IN**   | GPIO Pin (e.g., GPIO 26) | Controls the relay and humidifier |

🔹 **Important Notes:**
- Use the **Relay Module** to control the humidifier's power by switching its 5V supply.
- **Relay NO** (Normally Open) pin is used to connect the humidifier’s **VCC** to the 5V supply when the relay is activated.
- **GPIO 26** is used to control the relay; setting it **HIGH** activates the relay and turns on the humidifier, while setting it **LOW** turns the humidifier off.

---

**📜 Example Code**
```cpp
const int relayPin = 26;  // GPIO connected to relay module

void setup() {
  pinMode(relayPin, OUTPUT);  // Set relay pin as output
}

void loop() {
  digitalWrite(relayPin, HIGH);  // Turn humidifier ON by activating relay
  delay(5000);                   // Keep it ON for 5 sec
  digitalWrite(relayPin, LOW);   // Turn humidifier OFF by deactivating relay
  delay(5000);                   // Keep it OFF for 5 sec
}
```

---

### Extra
This section contains a collection of more complex hardware components, designed for those who are looking for a challenge. 

### 🔢 TM1638 LED and Key Module

<img src="https://cz.lnwfile.com/_/cz/_raw/z2/ef/3l.jpg" alt="TM1638 LED and Key module" width="350">

Image Source: [[Arduino4Pro](https://cz.lnwfile.com/_/cz/_raw/z2/ef/3l.jpg)]

The **TM1638 LED and Key Module** is a versatile component that combines **8 7-segment LED displays**, **8 push buttons**, and **8 LEDs**. It is commonly used in projects that require both display and user input. The module communicates with the ESP32 using an **adapted SPI** interface, combining **MISO** and **MOSI** into a single data line.

---

**🛠 Wiring (To ESP32)**  
| Module Pin  | Connection              | Function                    |
|-------------|-------------------------|-----------------------------|
| **VCC**     | 5V Power Supply         | Powers the module           |
| **GND**     | ESP32 GND               | Common ground               |
| **DIO**     | GPIO Pin (e.g., GPIO 23) | Data Pin (combined MISO/MOSI)|
| **CLK**     | GPIO Pin (e.g., GPIO 22) | Clock Pin for Communication |
| **STB**     | GPIO Pin (e.g., GPIO 21) | Latch Pin for Communication |

🔹 **Important Notes:**
- The **DIO** pin is used for data transfer between the ESP32 and the TM1638 module, combining both MISO and MOSI.
- The **CLK** pin is the clock pin used to synchronize data transfer.
- The **STB** pin is used to latch the data for updating the display or reading keypad input.

The module contains:
- **8 7-segment LED displays**: Each can show a digit from 0 to 9.
- **8 LEDs**: These can be turned on or off for visual feedback.
- **8 push buttons**: Used for user input.

---

**📜 Example Code**
```cpp
#include <TM1638.h>

// Define the pins connected to the TM1638 module
#define TM1638_DIO    23   // Data pin (combined MISO/MOSI)
#define TM1638_CLK    22   // Clock pin
#define TM1638_STB    21   // Strobe pin

// Create an instance of the TM1638 class
TM1638 tm1638(TM1638_CLK, TM1638_STB, TM1638_DIO);

void setup() {
  // Initialize the TM1638 module
  tm1638.begin();
  tm1638.setBrightness(7);  // Set the brightness of the LEDs
}

void loop() {
  // Display a number on the 7-segment display
  tm1638.displayInt(1234);  // Display the number 1234
  
  // Read the keypad input and print the key pressed to Serial Monitor
  byte key = tm1638.readKey();
  if (key != 0) {
    Serial.print("Key Pressed: ");
    Serial.println(key);
  }

  // Turn on the first LED
  tm1638.setLED(0, true);  // Turns on the first LED
  
  delay(500);  // Delay for half a second before next update
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
---
### BME680 Air Quality, Temperature, Pressure, and Humidity Sensor

<img src="https://shop.pimoroni.com/cdn/shop/products/BME680Breakout_1of2_768x768_crop_center.jpg" alt="BME680 air quality, temperature, pressure and humidity sensor" width="350"/>  

Image Source: [[Pimoroni](https://shop.pimoroni.com/cdn/shop/products/BME680Breakout_1of2_768x768_crop_center.jpg)]


The **BME680** is a powerful sensor from Bosch that provides **temperature**, **humidity**, **pressure**, and **gas resistance** (air quality) readings. It is widely used in environmental monitoring projects, especially in applications that require measuring indoor air quality. The sensor uses the **I2C** communication protocol, making it easy to interface with the ESP32.

---

**🛠 Wiring (To ESP32)**  
| Module Pin  | Connection            | Function                    |
|-------------|-----------------------|-----------------------------|
| **VCC**     | 3.3V Power Supply     | Powers the sensor           |
| **GND**     | ESP32 GND             | Common ground               |
| **SCL**     | GPIO 22               | I2C Clock                   |
| **SDA**     | GPIO 21               | I2C Data                    |

---

**📜 Example Code**
```cpp
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME680.h>

// Create an instance of the BME680 sensor
Adafruit_BME680 bme680;

void setup() {
  Serial.begin(115200);

  // Initialize I2C communication
  Wire.begin();

  // Initialize the BME680 sensor
  if (!bme680.begin()) {
    Serial.println("Failed to initialize BME680 sensor!");
    while (1);
  }

  Serial.println("BME680 sensor initialized.");
}

void loop() {
  // Request data from the BME680 sensor
  if (bme680.performReading()) {
    // Print the sensor readings to Serial Monitor
    Serial.print("Temperature: ");
    Serial.print(bme680.temperature);
    Serial.print(" °C\t");

    Serial.print("Humidity: ");
    Serial.print(bme680.humidity);
    Serial.print(" %\t");

    Serial.print("Pressure: ");
    Serial.print(bme680.pressure / 100.0);  // Convert to hPa
    Serial.print(" hPa\t");

    Serial.print("Gas Resistance: ");
    Serial.print(bme680.gas_resistance);
    Serial.println(" ohms");
  } else {
    Serial.println("Error reading from BME680 sensor.");
  }

  delay(2000);  // Delay before next reading
}
```
---
### Analog Turbidity Sensor

<img src="https://static.cytron.io/image/cache/catalog/New%20Temporary%20Product/90019%20(1)-800x800.jpg" alt="Analog turbidity sensor" width="350"/>  

Image Source: [[Digikey](https://static.cytron.io/image/cache/catalog/New%20Temporary%20Product/90019%20(1)-800x800.jpg)]

The **Analog Turbidity Sensor** is used to measure the turbidity or clarity of water, which is an important parameter for water quality testing. The sensor provides an **analog output** that corresponds to the turbidity level in the water. Higher turbidity means the water is murkier, while lower turbidity indicates clearer water. This sensor can be used in environmental monitoring projects, such as water pollution detection or water treatment systems.

---

**🛠 Wiring (To ESP32)**  
| Module Pin  | Connection            | Function                    |
|-------------|-----------------------|-----------------------------|
| **VCC**     | 3.3V Power Supply     | Powers the sensor           |
| **GND**     | ESP32 GND             | Common ground               |
| **AOUT**    | GPIO 34               | Analog Output (Turbidity)   |

---

**📜 Example Code**
```cpp
const int turbidityPin = 34;  // Define the GPIO pin connected to the AOUT pin of the sensor
int turbidityValue = 0;       // Variable to store turbidity value

void setup() {
  Serial.begin(115200);       // Initialize serial communication
  pinMode(turbidityPin, INPUT);  // Set turbidity pin as input
}

void loop() {
  turbidityValue = analogRead(turbidityPin);  // Read the analog value from the sensor
  Serial.print("Turbidity Level: ");
  Serial.println(turbidityValue);  // Print the turbidity level to Serial Monitor

  delay(1000);  // Delay before next reading
}
```
---
### MQTT for ESP32
The **MQTT** (Message Queuing Telemetry Transport) protocol is a lightweight messaging protocol commonly used for communication between devices in the **Internet of Things (IoT)**. It allows devices to send and receive messages in a **publish/subscribe** (PubSub) model, where devices can publish messages to topics and subscribe to topics to receive messages.

In this example, we will explore how to set up an **ESP32** to publish and subscribe to MQTT topics. This allows the ESP32 to send data to other devices or systems and receive data based on topics of interest.

#### Requirements:
- **Hardware:**  
  - ESP32 board
  - MQTT broker
  - Wi-Fi network for the ESP32

- **Software:**  
  - **PubSubClient** library for MQTT communication. Install the library via the Arduino Library Manager.

---
#### Wi-Fi Access Point Setup

For the duration of the workshop, a **Wi-Fi access point** will be available for all teams to connect to. Please use the provided Wi-Fi credentials to connect your ESP32 and other devices.

- **Wi-Fi SSID:** `Exploratory`
- **Password:** `!tggs2025`

Once connected, the ESP32 will be able to communicate with the local MQTT server.

#### MQTT Server IP Address

The local **MQTT broker** is hosted on the server with the following **IP address** and **Port number**:

- **MQTT Server IP Address:** `202.44.44.233`
- **Port:** `1883`

Make sure to configure your ESP32 to connect to this server for publishing and subscribing to topics.

---
#### Publish to a Single Topic

To publish to a single topic, the ESP32 sends a message to a specific topic, and any device subscribed to that topic will receive the message.

**📜 Example Code to Publish to a Single Topic:**
```cpp
#include <WiFi.h>
#include <PubSubClient.h>

// Wi-Fi and MQTT Broker details
const char* ssid = "Exploratory";
const char* password = "!tggs2025";
const char* mqttServer = "202.44.44.233";
const int mqttPort = 1883;
const char* mqttTopic = "TeamName/esp32/example";

// Initialize Wi-Fi and MQTT client
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to Wi-Fi");

  // Connect to MQTT broker
  client.setServer(mqttServer, mqttPort);
  while (!client.connected()) {
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT broker");
    } else {
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  // Publish message to the topic
  client.publish(mqttTopic, "Hello from ESP32!");
  delay(2000);  // Publish every 2 seconds
}

void reconnect() {
  while (!client.connected()) {
    if (client.connect("ESP32Client")) {
      Serial.println("Reconnected to MQTT broker");
    } else {
      delay(5000);
    }
  }
}
```
#### Publish to Several Topics

To publish to several topics, you can use multiple **publish()** calls to send data to different topics.

**📜 Example Code to Publish to Multiple Topics:**
```cpp
#include <WiFi.h>
#include <PubSubClient.h>

// Wi-Fi credentials
const char* ssid = "Exploratory";
const char* password = "!tggs2025";

// MQTT Broker details
const char* mqttServer = "202.44.44.233";
const int mqttPort = 1883;

// Topics for publishing messages
const char* topic1 = "TeamName/esp32/topic1";
const char* topic2 = "TeamName/esp32/topic2";

// Create a Wi-Fi and MQTT client
WiFiClient espClient;
PubSubClient client(espClient);

// Function to reconnect to the MQTT broker
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed to connect. Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");

  // Set up MQTT client
  client.setServer(mqttServer, mqttPort);

  // Attempt to connect to MQTT broker
  while (!client.connected()) {
    reconnect();
  }
}

void loop() {
  // Ensure the MQTT client remains connected
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  // Publish to multiple topics
  client.publish(topic1, "Message to Topic 1");
  client.publish(topic2, "Message to Topic 2");
  Serial.println("Messages published to Topic 1 and Topic 2");

  delay(2000);  // Publish every 2 seconds
}
```
### Subscribe to a Single Topic

To subscribe to a topic, the ESP32 listens for messages sent to that topic and processes them when they arrive.

**📜 Example Code to Subscribe to a Single Topic:**
```cpp
#include <WiFi.h>
#include <PubSubClient.h>

// Wi-Fi credentials
const char* ssid = "Exploratory";
const char* password = "!tggs2025";

// MQTT Broker details
const char* mqttServer = "202.44.44.233";
const int mqttPort = 1883;
const char* subscribeTopic = "Teamname/esp32/example";

// Create a Wi-Fi and MQTT client
WiFiClient espClient;
PubSubClient client(espClient);

// Function to reconnect to the MQTT broker
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT broker");
      // Subscribe to the topic once connected
      client.subscribe(subscribeTopic);
    } else {
      Serial.print("Failed to connect. Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

// Callback function for MQTT message handling
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.print(topic);
  Serial.print(" - ");
  
  // Print the received message
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");

  // Set up MQTT client
  client.setServer(mqttServer, mqttPort);
  client.setCallback(mqttCallback);

  // Attempt to connect to MQTT broker
  while (!client.connected()) {
    reconnect();
  }
}

void loop() {
  // Ensure the MQTT client remains connected
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
```
### Subscribe to Several Topics
To subscribe to several topics, you can call **subscribe()** multiple times for each topic.

**📜 Example Code to Subscribe to Several Topics:**
```cpp
#include <WiFi.h>
#include <PubSubClient.h>

// Wi-Fi credentials
const char* ssid = "Exploratory";
const char* password = "!tggs2025";

// MQTT Broker details
const char* mqttServer = "!tggs2025";
const int mqttPort = 1883;
const char* topic1 = "Teamname/esp32/topic1";
const char* topic2 = "Teamname/esp32/topic2";

// Create a Wi-Fi and MQTT client
WiFiClient espClient;
PubSubClient client(espClient);

// Function to reconnect to the MQTT broker
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) {
      Serial.println("Connected to MQTT broker");
      // Subscribe to topics once connected
      client.subscribe(topic1);
      client.subscribe(topic2);
    } else {
      Serial.print("Failed to connect. Retrying in 5 seconds...");
      delay(5000);
    }
  }
}

// Callback function for MQTT message handling
void mqttCallback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message received on topic: ");
  Serial.print(topic);
  Serial.print(" - ");
  
  // Print the received message
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");

  // Set up MQTT client
  client.setServer(mqttServer, mqttPort);
  client.setCallback(mqttCallback);

  // Attempt to connect to MQTT broker
  while (!client.connected()) {
    reconnect();
  }
}

void loop() {
  // Ensure the MQTT client remains connected
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
```
---
## Publish as JSON object to MQTT

This example demonstrates how to publish 3 values, packed as a JSON object, to an MQTT topic using an ESP32. The values represent **temperature**, **humidity**, and **pressure**.

### Prerequisites:
- Install the [ArduinoJson](https://github.com/bblanchon/ArduinoJson) library for JSON handling.
- Install the [PubSubClient](https://github.com/knolleary/pubsubclient) library for MQTT communication.

### Required Libraries:
- **WiFi**
- **PubSubClient** (for MQTT)
- **ArduinoJson** (for JSON creation)

### Example Code:

```cpp
#include <WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>  // Include the Arduino JSON library

// Wi-Fi credentials
const char* ssid = "Exploratory";
const char* password = "!tggs2025";

// MQTT Broker settings
const char* mqttServer = "202.44.44.233";
const int mqttPort = 1883;
const char* mqttTopic = "Teamname/sensors/data";  // The topic to publish to

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to Wi-Fi");

  // Connect to MQTT broker
  client.setServer(mqttServer, mqttPort);
  while (!client.connected()) {
    if (client.connect("ESP32Client", mqttUser, mqttPassword)) {
      Serial.println("Connected to MQTT broker");
    } else {
      Serial.print("Failed to connect, retrying...");
      delay(5000);
    }
  }
}

void loop() {
  // Create a JSON object
  StaticJsonDocument<200> doc;

  // Add sensor data to the JSON object
  doc["temperature"] = 25.5;  // Example: Temperature in Celsius
  doc["humidity"] = 60;       // Example: Humidity in percentage
  doc["pressure"] = 1015;     // Example: Pressure in hPa

  // Serialize the JSON object to a string
  char jsonBuffer[512];
  serializeJson(doc, jsonBuffer);

  // Publish the JSON string to MQTT topic
  if (client.publish(mqttTopic, jsonBuffer)) {
    Serial.println("Data published successfully");
  } else {
    Serial.println("Failed to publish data");
  }

  delay(2000);  // Publish every 2 seconds
}
```

---
### I2C Communication

I2C (Inter-Integrated Circuit) is a communication protocol commonly used to connect sensors and peripherals to microcontrollers, including the ESP32. It is a two-wire protocol that allows multiple devices to communicate with a single microcontroller using only two pins: **SDA (Serial Data)** and **SCL (Serial Clock)**.

#### Key Features:
- **Two-wire communication**: I2C only requires two wires for communication between the master (ESP32) and multiple slave devices.
- **Address-based communication**: Each I2C device has a unique address, allowing multiple devices to share the same data bus.
- **Master-slave model**: The microcontroller (master) controls the communication, and sensors or peripherals (slaves) respond to the master’s requests.

#### Wiring:
- **SDA** (Data Line) connects to GPIO21 on the ESP32 by default.
- **SCL** (Clock Line) connects to GPIO22 on the ESP32 by default.
- **VCC** and **GND** connect to the respective power and ground pins of the I2C devices.

#### Example Devices Using I2C:
- Sensors like the **BH1750 Light sensor**, **BME680 Air Quality Sensor**, and **GY-906 Temperature Sensor**.
- Displays such as **OLED displays**.

I2C is a simple and efficient way to add multiple sensors or devices to your project while minimizing the number of required pins. In Arduino code, I2C devices are typically accessed using libraries like `Wire.h` to handle the communication.

---

### End Device: Environmental Measurement System

The "End Device" is a comprehensive environmental monitoring system designed to collect key atmospheric data for both indoor and outdoor applications. It continuously measures vital parameters, which include:

- **CO2** (ppm)  
- **O2** (%)  
- **UV**  
- **Illuminance** (lux)  
- **Temperature** (°C)  
- **Pressure** (hPa)  
- **Humidity** (%)  
- **Altitude** (m)  
- **Gas Resistance** (Ohm)  
- **PM1** (µg/m³)  
- **PM2.5** (µg/m³)  
- **PM10** (µg/m³)  

The end devices are fully operational and are **online**, actively **publishing** real-time data to the MQTT server at `202.44.44.233:1883`. The data is published under the following topics:

- **Indoor Sensors**: `indoor/env_sensors`  
- **Outdoor Sensors**: `outdoor/env_sensors`  

This allows for remote monitoring and easy integration with IoT platforms for further analysis and control.
