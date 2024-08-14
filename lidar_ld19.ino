#include <Arduino.h>
#include "ld19_driver.h"

Ld19Driver ld19(&Serial1);

void setup() {
  Serial.begin(9600);
}

void loop() {
  double *degree;
  double *distance;
  uint8_t size;
  ld19.GetLidarAngleAndRange(&degree, &distance, size);
  for (int i = 0; i < size; i++) {
    Serial.print("degree: ");
    Serial.print(degree[i]);
    Serial.print(", distance: ");
    Serial.println(distance[i]);
  }
}