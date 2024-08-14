/**
 * @file ld19_driver.h
 * @author RinYoshida
 * @brief ld19のドライバクラス
 * @date 2024-08-13
 */

#ifndef LD19_DRIVER_H
#define LD19_DRIVER_H

#include <Arduino.h>
class Ld19Driver {
public:
    /**
     * @brief Construct a new Ld19Driver object
     * @param uart
     */
    Ld19Driver(HardwareSerial* uart);

    /**
     * @brief Destroy the Ld19Driver object
     */
    ~Ld19Driver();
    
    /**
     * @brief LD19のデータを取得する
     * @return uint8_t
     * @return 0: 正常終了
     * @return -1: シリアルポートにバッファがない
     * @return -2: CRCcheckエラー(実装されてません)
     */
    uint8_t GetLd19RawData(uint8_t **data, uint16_t &size);

    /**
     * @brief Get the Ld 1 9 Data object
     * @param speed 
     * @param startAngle 
     * @param endAngle 
     * @param timestamp 
     * @param distance 
     * @param intensity 
     * @return uint8_t 
     */
    uint8_t GetLidarAngleAndRange(double **degree, double **distance, uint8_t &size);

private:
    HardwareSerial* uart_;
    constexpr static uint8_t kLd19DataHead = 0x54;
    constexpr static uint8_t kLd19VerLen = 0x2C;
    constexpr static uint8_t kTotalByte = 47;
    constexpr static uint8_t kPointSize = 12;
};
#endif // LD19_DRIVER=H
