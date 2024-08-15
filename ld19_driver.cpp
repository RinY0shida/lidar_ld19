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

int8_t Ld19Driver::GetLd19RawData(uint8_t **data, uint16_t &size) {
  uint16_t count = 0;
  do {
    if (uart_->read() == kLd19DataHead) {
      if(uart_->read() == kLd19VerLen) {
        break;
      }
    }
  }while(count++ < 1000);

  if (count >= 1000) {
    return -1;
  }

  for (int i = 0; i < kTotalByte - 2; i++) {
    while (uart_->available() < 1) {
    }
    frame_data_[i + 2] = uart_->read();
  }

  frame_data_[0] = kLd19DataHead;
  frame_data_[1] = kLd19VerLen;
   // TODO: CRCcheckしたい return -2

  *data = frame_data_;
  size = kTotalByte;

  return 0;
}

int8_t Ld19Driver::GetLidarAngleAndRange(double **degree, double **distance, uint8_t &size) {
  uint8_t *data = nullptr;
  uint16_t data_size;

  if (this->GetLd19RawData(&data, data_size) == 0) {
    double start_angle = (((uint16_t)data[4] | ((uint16_t)data[5] << 8))) / 100.0;
    double end_angle = (((uint16_t)data[42] | ((uint16_t)data[43] << 8))) / 100.0;
    double step = end_angle - start_angle;
    if (step < 0) {
      step += 360;
    }
    step = step / (kPointSize - 1);
    for (int i = 0; i < kPointSize; i++) {
      distance_data_[i] = ((uint16_t)data[6 + 3 * i] | (uint16_t)data[7 + 3 * i] << 8) / 100.0;
      degree_data_[i] = start_angle + step * i;
      if (degree_data_[i] >= 360.0) {
          degree_data_[i] = fmod(degree_data_[i], 360.0);
      }
    }
  }
  *degree = degree_data_;
  *distance = distance_data_;
  size = kPointSize;
  return 0;
}
