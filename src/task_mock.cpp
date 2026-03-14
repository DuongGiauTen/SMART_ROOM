#include "task_mock.h"
#include "global.h"
#include <Arduino.h>

void taskMock_Execution(void *pvParameters) {
  while(1) {
    // Random nhiệt độ từ 25.0 đến 35.0
    g_temp = random(250, 350) / 10.0; 
    // Random độ ẩm từ 60.0 đến 90.0
    g_humid = random(600, 900) / 10.0;
    
    // Đảo trạng thái PIR (Giả lập có người ra vào)
    g_isMotion = !g_isMotion;

    // vTaskDelay: Báo cho FreeRTOS biết Task này xin "ngủ" 5000 ticks (5 giây).
    // Trong lúc nó ngủ, CPU sẽ chạy đi làm việc khác (đọc RFID, quét Keypad...).
    vTaskDelay(pdMS_TO_TICKS(5000)); 
  }
}