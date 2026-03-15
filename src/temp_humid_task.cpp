#include "temp_humid_task.h"
#include "global.h"
#include <DHT20.h>

DHT20 dht20;

void temp_humid_task(void *pvParameters) {
    dht20.read();
    while(1) {
        // Cập nhật biến toàn cục từ cảm biến
        g_temp = dht20.getTemperature();
        g_humid = dht20.getHumidity();

        Serial.print("Temperature: "); Serial.print(g_temp,2);
        Serial.print(" °C, Humidity: "); Serial.print(g_humid,2);
        Serial.println(" %");

        // vTaskDelay: Báo cho FreeRTOS biết Task này xin "ngủ" 1000 ticks (1 giây).
        // Trong lúc nó ngủ, CPU sẽ chạy đi làm việc khác (đọc RFID, quét Keypad...).
        vTaskDelay(pdMS_TO_TICKS(1000)); 
    }
}