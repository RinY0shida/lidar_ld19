/**
 * @file ld19_data.h
 * @author RinYoshida
 * @brief ld19のデータ用
 * @date 2024-08-13
 */
#ifndef LIDAR_LD19_LD19_DATA_H
#define LIDAR_LD19_LD19_DATA_H

struct Ld19Data {
public:
    ld19_data(double rad, uint16_t distance)
     : rad_(rad), 
       distance_(distance) {}
    double rad_;
    uint16_t distance_;
};

struct LidatPoint {
public:
    LidarPoint(uint16_t distance, uint8_t intensity)
     : distance_(distance), 
       intensity_(intensity) {}
    uint16_t distance_;
    uint8_t intensity_;
};

struct Ld19RawData {
public:
    Ld19RawData(uint16_t speed, uint16_t start_angle, LidarPoint points[12], uint16_t end_angle, uint16_t timestamp, uint8_t crc)
     : speed_(speed),
       start_angle_(start_angle),
       points_(points), end_angle_(end_angle), 
       timestamp_(timestamp), 
       crc_(crc) {}
    uint8_t header_;
    uint8_t var_len_;
    uint16_t speed_;
    uint16_t start_angle_;
    LidarPoint points_[12];
    uint16_t end_angle_;
    uint16_t timestamp_;
    uint8_t crc_;
};

#endif  // LIDAR_LD19_LD19_DATA_H

