#ifndef CONFIG_H
#define CONFIG_H

// ==========================================
// THÔNG TIN MẠNG & ADAFRUIT IO
// ==========================================
#define WIFI_SSID       "TEN_WIFI_CUA_BAN"
#define WIFI_PASS       "MAT_KHAU_WIFI"
#define AIO_USERNAME    "TEN_USER_ADAFRUIT"
#define AIO_KEY         "KEY_ADAFRUIT_CUA_BAN"
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883

// ==========================================
// ĐỊNH NGHĨA CHÂN (PINOUT) CHO YOLO UNO (ESP32-S3)
// ==========================================
// 1. LCD I2C
#define I2C_SDA         11
#define I2C_SCL         12

// 2. Servo, LED, Quạt
#define SERVO_PIN       47 // D12 trên Yolo Uno
#define LED_PIN         1  // Giả lập Đèn (Ví dụ chân D0/RX)
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


#endif