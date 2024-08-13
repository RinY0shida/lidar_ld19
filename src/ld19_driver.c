/**
 * @file ld19_driver.c
 * @author RinYoshida
 * @brief ld19のドライバクラス
 * @date 2024-08-13
 */

#include "lidar_ld19/ld19_driver.h"

LD19Driver::LD19Driver(HardwareSerial* uart) : uart_(uart) {
    uart_->begin(230400);
}

LD19Driver::~LD19Driver() {
    uart_->end();
}

uint8_t LD19Driver::GetLd19RawData(uint8_t *data, uint16_t &size) {
    if (!uart_->available()) return -1;

    std::vector<uint8_t> byte;
    uint8_t buf;

    while (1) {
        buf = uart_->read();
        if (buf == kLd19DataHead && byte.size() == 0) {
            byte.push_back(buf);
            continue;
        }

        
        if (byte.size() > 0 && byte.size() < kTotalByte) {
            byte.push_back(buf);
            if (byte[1] != kLd19VerLen) {
                byte.clear();
                continue;
            }
        }
        else if (byte.size() == kTotalByte) {
             // Check CRC
            uint8_t crc = CalcCrc(byte.data(), kTotalByte - 1);
            if (crc != byte[kTotalByte - 1]) {
                byte.clear();
                return -2;
            }
            break;
        }
        else {
            byte.clear();
        }
    }
    *data = byte.data();
    size = byte.size();
    return 0;
}

uint8_t LD19Driver::CalcCrc(uint8_t *data, uint16_t size) {
    uint8_t crc = 0;
    for (uint8_t i = 0; i < len; i++) {
        crc = CrcTable[(crc ^ data[i]) & 0xFF];
    }
    return crc;
}