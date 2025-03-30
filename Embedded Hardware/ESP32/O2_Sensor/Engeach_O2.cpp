#include "Engeach_O2.h"

// Constructor: ตั้งค่าขาอนาล็อก
Engeach_O2::Engeach_O2(uint8_t analogPin, float offset, float sensitivity) {
  pin = analogPin;
  offsetVoltage = offset;  // ตั้งค่า offsetVoltage
  sensitivityValue = sensitivity;  // ตั้งค่า sensitivity
}

// อ่านค่าแรงดันขาออก (V)
float Engeach_O2::readVout() {
  uint16_t rawValue = analogRead(pin);
  float voltage = (rawValue * 3.3) / ADC_RESOLUTION; // คำนวณแรงดัน (3.3V เป็นแรงดันอ้างอิง)
  return voltage;
}

// อ่านค่าจาก analogRead
uint16_t Engeach_O2::readValue() {
  return analogRead(pin);
}

void Engeach_O2::sortArray(int16_t arr[], int16_t size) {
  for (int16_t i = 0; i < size - 1; i++) {
    for (int16_t j = 0; j < size - i - 1; j++) {
      if (arr[j] > arr[j + 1]) {
        int16_t temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}

void Engeach_O2::showparameter(){
  Serial.print("offset voltage for zero ppm: ");
  Serial.print(offsetVoltage,3);
  Serial.println(" V");
  Serial.print("sensitivity: ");
  Serial.print(sensitivityValue,3);
  Serial.println(" uA");
  Serial.print("MCU ADC RESOLUTION : ");
  Serial.println(ADC_RESOLUTION,0);
}

int16_t Engeach_O2::calculateAverage(int16_t arr[], int16_t size) {
  int16_t sum = 0;
  for (int16_t i = 0; i < size; i++) {
    sum += arr[i];
  }
  return sum / size;
}

// คำนวณความเข้มข้น O2 เป็น %
float Engeach_O2::getO2_percentage() {
  const int16_t numReadings = 10; // จำนวนการอ่านข้อมูล
  int16_t readings[numReadings]; // อาร์เรย์เก็บค่าที่อ่าน
  
  // อ่านค่าจากเซ็นเซอร์หลายครั้ง
  for (int16_t i = 0; i < numReadings; i++) {
    readings[i] = analogRead(pin);
    delay(1); // รอ 0.05 วินาที
  }
  
  // เรียงลำดับค่าที่อ่าน
  sortArray(readings, numReadings);
  
  // ตัดค่า outlier ที่สุดโต่ง (ค่าต่ำสุดและสูงสุด)
  int16_t filteredReadings[6];
  for (int16_t i = 2; i < numReadings - 2; i++) {
    filteredReadings[i - 2] = readings[i];
  }

  // คำนวณค่าเฉลี่ยของค่าที่กรองแล้ว
  int16_t avg = calculateAverage(filteredReadings, 6);

  // กรองข้อมูลโดยกำจัดค่าที่เบี่ยงเบนเกิน 20% ของค่าเฉลี่ย
  int16_t validCount = 0;
  int16_t finalReadings[6];
  for (int16_t i = 0; i < 6; i++) {
    if (abs(filteredReadings[i] - avg) <= avg * 0.2) {
      finalReadings[validCount] = filteredReadings[i];
      validCount++;
    }
  }

  // คำนวณค่าเฉลี่ยสุดท้าย
  int16_t finalAverage = 0;
  if (validCount > 0) {
    finalAverage = calculateAverage(finalReadings, validCount);
  }

  // แปลงค่าเฉลี่ยเป็นแรงดัน (V)
  float voltage_ppm = (finalAverage * 3.3) / ADC_RESOLUTION;

  // คำนวณ ppm โดยใช้ offsetVoltage
  float percentage = ((voltage_ppm - offsetVoltage) / (((sensitivityValue*100)/1000000)*220)); // ((100uA*100Ω)/1000000)x220GAIN (GAIN at 25°C)

  return percentage > 0 ? percentage : 0; // ป้องกันค่าติดลบ
}

float Engeach_O2::getO2_calibateSensitivity() {
  const int16_t numReadings = 10; // จำนวนการอ่านข้อมูล
  int16_t readings[numReadings]; // อาร์เรย์เก็บค่าที่อ่าน
  
  // อ่านค่าจากเซ็นเซอร์หลายครั้ง
  for (int16_t i = 0; i < numReadings; i++) {
    readings[i] = analogRead(pin);
    delay(1); // รอ 0.05 วินาที
  }
  
  // เรียงลำดับค่าที่อ่าน
  sortArray(readings, numReadings);
  
  // ตัดค่า outlier ที่สุดโต่ง (ค่าต่ำสุดและสูงสุด)
  int16_t filteredReadings[6];
  for (int16_t i = 2; i < numReadings - 2; i++) {
    filteredReadings[i - 2] = readings[i];
  }

  // คำนวณค่าเฉลี่ยของค่าที่กรองแล้ว
  int16_t avg = calculateAverage(filteredReadings, 6);

  // กรองข้อมูลโดยกำจัดค่าที่เบี่ยงเบนเกิน 20% ของค่าเฉลี่ย
  int16_t validCount = 0;
  int16_t finalReadings[6];
  for (int16_t i = 0; i < 6; i++) {
    if (abs(filteredReadings[i] - avg) <= avg * 0.2) {
      finalReadings[validCount] = filteredReadings[i];
      validCount++;
    }
  }

  // คำนวณค่าเฉลี่ยสุดท้าย
  int16_t finalAverage = 0;
  if (validCount > 0) {
    finalAverage = calculateAverage(finalReadings, validCount);
  }

  // แปลงค่าเฉลี่ยเป็นแรงดัน (V)
  float voltage_ppm = (finalAverage * 3.3) / ADC_RESOLUTION;

  // คำนวณ ppm โดยใช้ offsetVoltage
  float sensitivityValue = ((((voltage_ppm - offsetVoltage) / 20.9)/220)*1000000)/100; // ((100uA*100Ω)/1000000)x220GAIN (GAIN at 25°C)


  return sensitivityValue > 0 ? sensitivityValue : 0; // ป้องกันค่าติดลบ
}
