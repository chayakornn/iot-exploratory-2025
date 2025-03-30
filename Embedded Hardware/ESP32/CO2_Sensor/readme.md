### MH-Z19C CO₂ Sensor

The **MH-Z19C** is a compact **NDIR (Non-Dispersive Infrared) CO₂ sensor** that provides accurate carbon dioxide (CO₂) measurements. It supports both **UART (serial)** and **PWM output** for data communication.

<img src="https://cdn-reichelt.de/resize/600%2F-/web/xxl_ws/C150%2FMH-Z19C-PC_1.png" alt="MH-Z19C CO2 sensor" width="350">
  
*Image Source: [[Reichelt.de](https://cdn-reichelt.de/resize/600%2F-/web/xxl_ws/C150%2FMH-Z19C-PC_1.png)]*  

#### 🛠 Hardware Required

- **MH-Z19C CO₂ Sensor**
- **ESP32 Development Board**
- **Jumper Wires**
- **Stable 5V Power Supply**

#### 🔧 Wiring (To ESP32)

| MH-Z19C Pin | ESP32 Pin  | Description |
|-------------|-----------|-------------|
| **VCC**     | **5V**    | Power supply (5V required) |
| **GND**     | **GND**   | Ground |
| **TX**      | **GPIO16** | Sensor TX → ESP32 RX |
| **RX**      | **GPIO17** | Sensor RX → ESP32 TX |

#### 📜 Example Code (UART Mode)

```cpp
#include "MHZ19_uart.h"

const int rx_pin = 16; //Serial rx pin no
const int tx_pin = 17; //Serial tx pin no

MHZ19_uart mhz19;

void setup()
{
  Serial.begin(9600);
  mhz19.begin(rx_pin, tx_pin);
  mhz19.setAutoCalibration(false);

  Serial.println("MH-Z19 is warming up now.");
  delay(10 * 1000); //
}

void loop()
{
  int co2ppm = mhz19.getCO2PPM();
  int temp = mhz19.getTemperature();

  Serial.print("co2: ");
  Serial.println(co2ppm);
  delay(5000);
