#include "device.h"
#include "global.h"
#include "config.h"

void device_task(void *pvParameters) {

    while(1) {

    //Light control
        if (g_ledState) {
            // Bật đèn
            digitalWrite(LED_PIN, HIGH);
        } else {
            // Tắt đèn
            digitalWrite(LED_PIN, LOW);
        }

        //Fan control

        if (g_fanState) {
            // Bật quạt
            digitalWrite(FAN_PIN, HIGH);
        } else {
            // Tắt quạt
            digitalWrite(FAN_PIN, LOW);
        }

        //Door control
        if (g_doorState) {
            // Mở cửa
            doorServo.write(90); // Góc mở cửa (có thể điều chỉnh tùy loại servo)
        } else {
            // Đóng cửa
            doorServo.write(0); // Góc đóng cửa
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}