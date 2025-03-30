#ifndef Engeach_O2_h
#define Engeach_O2_h

#include <Arduino.h>

// กำหนดค่าความละเอียด ADC ตามบอร์ดที่ใช้งาน
#ifdef ESP32
  #define ADC_RESOLUTION 4095.0 // 12-bit resolution for ESP32
#elif defined(ESP8266)
  #define ADC_RESOLUTION 1023.0 // 10-bit resolution for ESP8266
#elif defined(STM32F1xx)
  #define ADC_RESOLUTION 4095.0 // 12-bit resolution for STM32
#elif defined(ARDUINO_AVR_UNO) || defined(ARDUINO_AVR_UNO_R3)
  #define ADC_RESOLUTION 1023.0 // 10-bit resolution for Arduino Uno and Uno R3
#elif defined(ARDUINO_AVR_MEGA2560)
  #define ADC_RESOLUTION 1023.0 // 10-bit resolution for Arduino Mega 2560
#elif defined(ARDUINO_AVR_NANO)
  #define ADC_RESOLUTION 1023.0 // 10-bit resolution for Arduino Nano
#elif defined(ARDUINO_AVR_MICRO)
  #define ADC_RESOLUTION 1023.0 // 10-bit resolution for Arduino Micro
#elif defined(ARDUINO_AVR_MINI)
  #define ADC_RESOLUTION 1023.0 // 10-bit resolution for Arduino Mini
#elif defined(ARDUINO_ARCH_SAMD)
  #define ADC_RESOLUTION 4095.0 // 12-bit resolution for SAMD boards (e.g., Arduino Zero)
#elif defined(ARDUINO_SAMD_MKRZERO)
  #define ADC_RESOLUTION 4095.0 // 12-bit resolution for MKR Zero
#elif defined(ARDUINO_SAMD_MKR1000)
  #define ADC_RESOLUTION 4095.0 // 12-bit resolution for MKR1000
#elif defined(ARDUINO_SAMD_NANO_33_IOT)
  #define ADC_RESOLUTION 4095.0 // 12-bit resolution for Nano 33 IoT
#elif defined(TEENSYDUINO)
  #if defined(__IMXRT1062__) // Teensy 4.x
    #define ADC_RESOLUTION 4095.0 // 12-bit resolution for Teensy 4.x
  #elif defined(__MKL26Z64__) // Teensy LC
    #define ADC_RESOLUTION 4095.0 // 12-bit resolution for Teensy LC
  #elif defined(__MK20DX128__) || defined(__MK20DX256__) // Teensy 3.1/3.2
    #define ADC_RESOLUTION 4095.0 // 12-bit resolution for Teensy 3.1/3.2
  #else
    #define ADC_RESOLUTION 1023.0 // Default 10-bit resolution for other Teensy
  #endif
#elif defined(__AVR_ATtiny85__) || defined(__AVR_ATtiny84__)
  #define ADC_RESOLUTION 1023.0 // 10-bit resolution for ATtiny85/ATtiny84
#elif defined(ARDUINO_RASPBERRY_PI_PICO)
  #define ADC_RESOLUTION 4095.0 // 12-bit resolution for Raspberry Pi Pico
#elif defined(ARDUINO_ESP32S2_DEV)
  #define ADC_RESOLUTION 4095.0 // 12-bit resolution for ESP32-S2
#elif defined(ARDUINO_ESP32S3_DEV)
  #define ADC_RESOLUTION 4095.0 // 12-bit resolution for ESP32-S3
#elif defined(ARDUINO_RASPBERRY_PI_ZERO)
  #define ADC_RESOLUTION 4095.0 // 12-bit resolution for Raspberry Pi Zero
#elif defined(ARDUINO_MBED_NANO)
  #define ADC_RESOLUTION 4095.0 // 12-bit resolution for Nano RP2040 Connect
#elif defined(ARDUINO_NRF52_ADAFRUIT)
  #define ADC_RESOLUTION 4095.0 // 12-bit resolution for nRF52840 (Adafruit Bluefruit boards)
#else
  #define ADC_RESOLUTION 1023.0 // Default 10-bit resolution for other boards
#endif


class Engeach_O2 {
private:
  uint8_t pin;           // ขาอนาล็อกที่เชื่อมต่อกับเซ็นเซอร์
  float offsetVoltage;   // ค่า offset แรงดันของเซ็นเซอร์
  float sensitivityValue;   // ค่า sensitivity แรงดันของเซ็นเซอร์

public:
  // Constructor: ตั้งค่าขาอนาล็อก, offsetVoltage และ sensitivity
  Engeach_O2(uint8_t analogPin, float offset = 0.013, float sensitivity = 4.8);

  // อ่านค่าแรงดันขาออก (V)
  float readVout();

  // อ่านค่าจาก analogRead
  uint16_t readValue();

  // คำนวณความเข้มข้น O2 เป็น %
  float getO2_percentage();
  float getO2_calibateSensitivity(); 
  void sortArray(int16_t arr[], int16_t size);
  void showparameter();
  int16_t calculateAverage(int16_t arr[], int16_t size);
};

#endif
