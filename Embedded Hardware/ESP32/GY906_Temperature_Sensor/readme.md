### GY-906 MLX90614 Infrared Temperature Sensor

The **GY-906 MLX90614** is a **non-contact infrared temperature sensor** that measures surface temperatures without physical contact. It uses **I2C communication**, making it easy to interface with the **ESP32**.

<img src="https://o.lnwfile.com/_/o/_raw/ng/lp/q3.jpg" alt="GY906" width="350">
  
*Image Source: [[Arduitronics.com](https://o.lnwfile.com/_/o/_raw/ng/lp/q3.jpg)]*  

#### Library
[VEGA MLX90614 Sensor Library](https://gitlab.com/riscv-vega/vega-sensor-libraries/sensors/vega_mlx90614)

#### 🛠 Hardware Required

- **GY-906 MLX90614 IR Temperature Sensor**
- **ESP32 Development Board**
- **Jumper Wires**

#### 🔧 Wiring (To ESP32)

| MLX90614 Pin | ESP32 Pin  | Description  |
|--------------|-----------|--------------|
| **VCC**      | **3.3V**  | Power supply (3.3V required) |
| **GND**      | **GND**   | Ground |
| **SDA**      | **GPIO21** | I2C Data Line |
| **SCL**      | **GPIO22** | I2C Clock Line |

#### 📜 Example Code (I2C Mode)

```cpp
#include <Wire.h>
#include "VEGA_MLX90614.h"

#define SDA_PIN 21
#define SCL_PIN 22

VEGA_MLX90614 mlx(SDA_PIN, SCL_PIN);  // Use correct ESP32 I2C pins

void setup() {
  Wire.begin(SDA_PIN, SCL_PIN);  // Initialize I2C
  Serial.begin(115200);
  Serial.println("+-----[ MLX90614 Temperature Sensor with ESP32 ]-----+");
}

void loop() {
  double temperature;

  temperature = mlx.mlx90614ReadAmbientTempC();  // Read ambient temperature
  Serial.print("Ambient Temp: ");
  Serial.print(temperature);

  temperature = mlx.mlx90614ReadTargetTempC();   // Read target temperature
  Serial.print("   Target Temp: ");
  Serial.println(temperature);

  delay(500);
}
