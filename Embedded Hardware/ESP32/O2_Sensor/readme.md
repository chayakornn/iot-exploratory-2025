# Engeach O₂ Sensor (Analog Output)

This directory contains the **code** and **libraries** required to interface the **Engeach Oxygen (O₂) Sensor** with an **ESP32**.

<img src="https://robu.in/wp-content/uploads/2021/11/AO-03%E4%B8%BB%E5%9B%BE-1.jpg" alt="O2 Sensor" width="350">
  
*Image Source: [[Robu.in](https://robu.in/wp-content/uploads/2021/11/AO-03%E4%B8%BB%E5%9B%BE-1.jpg)]*  


## 📖 Description

The **Engeach O₂ Sensor** provides **analog voltage output** proportional to the oxygen concentration in the air. It requires **a stable power supply** and a high-resolution **ADC (Analog-to-Digital Converter)**, which the ESP32 provides.

## 🛠 Hardware Required

- **Engeach O₂ Sensor (Analog)**
- **ESP32 Development Board**
- **Jumper wires**
- **Stable 3.3V or 5V power source** (depending on sensor specifications)

## 🔧 Wiring (To ESP32)

| Sensor Pin | ESP32 Pin |
|------------|----------|
| **VCC**    | **3.3V** *(or 5V if required by the sensor)* |
| **GND**    | **GND** |
| **AOUT**   | **GPIO 34** *(or any ADC-capable pin)* |

## 📜 Example Code

```cpp
#include "Engeach_O2.h"

const uint8_t analogPin = 34;                             
const float offsetVoltage = 0.016;                        
const float sensitivity = 4.6;                            
Engeach_O2 o2Sensor(analogPin, offsetVoltage, sensitivity);

void setup() {
  Serial.begin(9600);                           
  o2Sensor.showparameter();                       
  Serial.print("Recommended sensitivity: ");
  Serial.print(o2Sensor.getO2_calibateSensitivity());     
  Serial.print(" uA/%");
  delay(200);
}

void loop() {
  float voltage = o2Sensor.readVout();     
  float percentage = o2Sensor.getO2_percentage(); 
  uint16_t rawValue = o2Sensor.readValue(); 

  Serial.print("Raw Value: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.print(voltage, 3);
  Serial.print(" V | O2: ");
  Serial.print(percentage);
  Serial.println(" %");
  //
  delay(200);
}
