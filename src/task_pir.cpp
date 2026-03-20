#include "task_pir.h"
#include "config.h"
#include "global.h"
#include <Arduino.h>

void taskPIR_Execution(void *pvParameters) {
    // 1. Khai báo chân PIR là chân Nhận tín hiệu (INPUT)
    pinMode(PIR_PIN, INPUT);
    
    Serial.println("PIR Sensor is Ready!");

    while(1) {
        // 2. Đọc trạng thái từ phần cứng
        int pirState = digitalRead(PIR_PIN);

        // 3. Cập nhật vào biến toàn cục của hệ thống
        if (pirState == HIGH) {
            g_isMotion = true;
            Serial.println("Motion Detected!");
        } else {
            g_isMotion = false;
            Serial.println("No Motion.");
        }

        // Nhường CPU 200ms (Cảm biến PIR không cần đọc quá nhanh)
        vTaskDelay(pdMS_TO_TICKS(5000)); 
    }
}