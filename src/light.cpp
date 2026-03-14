#include "light.h"
#include "global.h"
#include "config.h"

void light_task(void *pvParameters) {

    while(1) {
        if (g_ledState) {
            // Bật đèn
            digitalWrite(LED_PIN, HIGH);
        } else {
            // Tắt đèn
            digitalWrite(LED_PIN, LOW);
        }
    }
}