#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>
#include <ESP32Servo.h>

#define INITIAL 0
#define LED_CONTROL 1
#define FAN_CONTROL 2
#define DOOR_CONTROL 3

extern volatile uint32_t systemState; // Biến toàn cục để lưu trạng thái hiện tại của hệ thống (đèn, quạt, cửa)


// Từ khóa "extern" báo cho trình biên dịch biết: 
// "Biến này đã được tạo ở một nơi khác (global.cpp), hãy dùng chung nó nhé!"
// Từ khóa "volatile" bắt buộc dùng trong FreeRTOS để tránh trình biên dịch tối ưu hóa sai lệnh.


extern volatile float g_temp;
extern volatile float g_humid;
extern volatile bool g_isMotion;

extern volatile bool g_ledState;
extern volatile bool g_fanState;
extern volatile bool g_doorState;

// Dữ liệu hiển thị lên LCD
extern String g_lcdLine1;
extern String g_lcdLine2;

// Đối tượng Servo dùng chung cho cả Task Keypad và Task RFID
extern Servo doorServo;

#endif