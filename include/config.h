#ifndef CONFIG_H
#define CONFIG_H

#include "secret.h" // Chứa các thông tin nhạy cảm như key Adafruit IO
// ==========================================
// THÔNG TIN MẠNG & ADAFRUIT IO
// ==========================================
#define WIFI_SSID       "BKIT_ROOFTOP"    // TEN WIFI
#define WIFI_PASS       SECRET_WIFI_PASS       // MAT KHAU WIFI
#define AIO_USERNAME    "duongtran253"   // TEN USER ADAFRUIT (KHÔNG PHẢI KEY)
#define AIO_KEY         SECRET_ADAFRUIT_IO_KEY// KEY ADAFRUIT (DÙNG ĐỂ KẾT NỐI MQTT, KHÔNG PHẢI USERNAME)
#define AIO_SERVER      "io.adafruit.com"     // MÁY CHỦ MQTT CỦA ADAFRUIT
#define AIO_SERVERPORT  1883                  // CỔNG KẾT NỐI MQTT

// ==========================================
// ĐỊNH NGHĨA CHÂN (PINOUT) CHO YOLO UNO (ESP32-S3)
// ==========================================
// 1. LCD I2C
#define I2C_SDA         11
#define I2C_SCL         12

// 2. Servo, LED, Quạt
#define SERVO_PIN       38 // D12 trên Yolo Uno
#define LED_PIN         48  // Giả lập Đèn (Ví dụ chân D0/RX)
#define FAN_PIN         2  // Giả lập Quạt (Ví dụ chân D1/TX)

// 3. RFID RC522 (Sử dụng chuẩn SPI)
// ESP32-S3 cho phép map chân SPI tùy ý. Ở đây ta chọn các chân an toàn.
#define RFID_SCK        4 // Chân Clock
#define RFID_MISO       2 // Chân Master In Slave Out
#define RFID_MOSI       3 // Chân Master Out Slave In
#define RFID_SS         21 // Chân Chip Select (SDA trên module RFID)
#define RFID_RST        1 // Chân Reset

// 4. Keypad 4x4
#define ROW_NUM         4 
#define COLUMN_NUM      4

// 5. Set ngưỡng nhiệt độ
#define TEMP_THRESHOLD  30.0 // Ngưỡng nhiệt độ để bật quạt
#define HUMID_THRESHOLD 60.0 // Ngưỡng độ ẩm để cảnh báo



#endif