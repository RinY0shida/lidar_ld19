/**
 * @file ld19_driver.c
 * @author RinYoshida
 * @brief ld19のドライバクラス
 * @date 2024-08-13
 */

#include "math.h"

#include "ld19_driver.h"

Ld19Driver::Ld19Driver(HardwareSerial* uart) : uart_(uart) {
    uart_->begin(230400);
}

Ld19Driver::~Ld19Driver() {
    uart_->end();
}

uint8_t Ld19Driver::GetLd19RawData(uint8_t **data, uint16_t &size) {
  uint8_t frame_data[kTotalByte] = {0};
  if (Serial1.available() < 1) return -1;
  while (Serial1.read() != kLd19DataHead);
  while (Serial1.available() < 1) {}
  while (Serial1.read() != kLd19VerLen);
  for (int i = 0; i < kTotalByte - 2; i++) {
    while (Serial1.available() < 1) {
    }
    frame_data[i + 2] = Serial1.read();
  }

  frame_data[0] = kLd19DataHead;
  frame_data[1] = kLd19VerLen;
   // TODO: CRCcheckしたい return -1

  *data = frame_data;
  size = kTotalByte;

  return 0;
}

uint8_t Ld19Driver::GetLidarAngleAndRange(double **degree, double **distance, uint8_t &size) {
  uint8_t *data = nullptr;
  uint16_t data_size;
  double distance_data[kPointSize];
  double degree_data[kPointSize];
   // double intensity_data[kPointSize];

  while (this->GetLd19RawData(&data, data_size) == 0) {
    double start_angle = (((uint16_t)data[4] | ((uint16_t)data[5] << 8))) / 100.0;
    double end_angle = (((uint16_t)data[42] | ((uint16_t)data[43] << 8))) / 100.0;
    double step = end_angle - start_angle;
    if (step < 0) {
      step += 360;
    }
    step = step / (kPointSize - 1);
    for (int i = 0; i < kPointSize; i++) {
        distance_data[i] = ((uint16_t)data[6 + 3 * i] | (uint16_t)data[7 + 3 * i] << 8) / 100.0;
        degree_data[i] = start_angle + step * i;
        if (degree_data[i] >= 360.0) {
            degree_data[i] = fmod(degree_data[i], 360.0);
        }
    }
  }
  *degree = degree_data;
  *distance = distance_data;
  size = kPointSize;
  return 0;
}
