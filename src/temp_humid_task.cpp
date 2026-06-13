#include "temp_humid_task.h"
#include "global.h"
#include <DHT20.h>
#include "config.h"

DHT20 dht20;

void temp_humid_task(void *pvParameters) {
    while(1) {
        // Cập nhật biến toàn cục từ cảm biến
        dht20.read();
        float temp = dht20.getTemperature();
        float humi = dht20.getHumidity();
        g_temp = temp;
        g_humid = humi;

        Serial.print("Temperature: "); Serial.print(g_temp,2);
        Serial.print(" °C, Humidity: "); Serial.print(g_humid,2);
        Serial.println(" %");

        // if (g_temp >= TEMP_THRESHOLD) {
        //     Serial.println("Temperature threshold exceeded! Turning on fan...");
        //     g_fanState = true; 
        // } else {
        //     g_fanState = false; 
        // }

        // vTaskDelay: Báo cho FreeRTOS biết Task này xin "ngủ" 1000 ticks (1 giây).
        // Trong lúc nó ngủ, CPU sẽ chạy đi làm việc khác (đọc RFID, quét Keypad...).
        vTaskDelay(pdMS_TO_TICKS(5000)); 
    }
}