#include <Arduino.h>
#include "ld19_driver.h"

Ld19Driver ld19(&Serial1); // Ld19Driverのオブジェクトを生成

void setup() {
  Serial.begin(9600);
}

void loop() {
  double *degree;
  double *distance;
  uint8_t size;
  if (ld19.GetLidarAngleAndRange(&degree, &distance, size) == 0){
    for (int i = 0; i < size; i++) {
      Serial.print("degree: ");
      Serial.print(degree[i]);
      Serial.print("° , ");
      Serial.print("distance: ");
      Serial.print(distance[i] / 100.0);
      Serial.println("m");
    }
  }
  else {
    Serial.println("Error");
  }
}