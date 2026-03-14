#include "door.h"
#include "global.h"
#include "config.h"

void door_task(void *pvParameters) {
    while(1) {
        if (g_doorState) {
            // Mở cửa
            doorServo.write(180); 
        } else {
            // Đóng cửa
            doorServo.write(0); 
        }
        vTaskDelay(pdMS_TO_TICKS(100)); 
    }
}