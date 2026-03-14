#include "task_keypad.h"
#include "config.h"
#include "global.h"
#include <Keypad.h>

// Khai báo ma trận phím
char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte pin_rows[ROW_NUM] = {8, 7, 6, 5};
byte pin_column[COLUMN_NUM] = {9, 10, 17, 18};

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM);

void taskKeypad_Execution(void *pvParameters) {
  // Khởi tạo chân output cho LED và Quạt
  pinMode(LED_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  while(1) {
    char key = keypad.getKey();
    if (key) {
      Serial.println("Key pressed: " + String(key));
      
      if (key == '1') {
        g_ledState = !g_ledState;
        digitalWrite(LED_PIN, g_ledState ? HIGH : LOW);
        g_lcdLine1 = "Led Control";
        g_lcdLine2 = g_ledState ? "ON" : "OFF";
      } 
      else if (key == '2') {
        g_fanState = !g_fanState;
        digitalWrite(FAN_PIN, g_fanState ? HIGH : LOW);
        g_lcdLine1 = "Fan Control";
        g_lcdLine2 = g_fanState ? "ON" : "OFF";
      }
      else if (key == '3') {
        g_doorState = !g_doorState;
        doorServo.write(g_doorState ? 90 : 0); // Quay 90 độ để mở cửa
        g_lcdLine1 = "Door Control";
        g_lcdLine2 = g_doorState ? "Open" : "Close";
      }
    }
    // Ngủ 50ms để chống dội phím (Debounce) và nhường CPU
    vTaskDelay(pdMS_TO_TICKS(50)); 
  }
}