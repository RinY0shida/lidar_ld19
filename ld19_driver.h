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
    int8_t GetLd19RawData(uint8_t **data, uint16_t &size);

    /**
     * @brief Get the Ld 1 9 Data object
     * @param degree 角度
     * @param distance 距離
     * @param size 角度と距離の配列サイズ
     * @return int8_t
     * @return 0: 正常終了
     * @return -1: フレームが取得できなかった
     */
    int8_t GetLidarAngleAndRange(double **degree, double **distance, uint8_t &size);

    /**
     * @brief CRCの計算用関数
     * @param data 
     * @return crcの結果
     */
     // TODO(RinYoshida):　いつか実装する
    uint8_t CalcCrc(uint8_t *data);

private:
    HardwareSerial* uart_;
    constexpr static uint8_t kLd19DataHead = 0x54;
    constexpr static uint8_t kLd19VerLen = 0x2C;
    constexpr static uint8_t kTotalByte = 47;
    constexpr static uint8_t kPointSize = 12;
    double distance_data_[kPointSize];
    double degree_data_[kPointSize];
    uint8_t frame_data_[kTotalByte];

};
#endif // LD19_DRIVER=H
