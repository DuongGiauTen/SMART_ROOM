#include "task_lcd.h"
#include "config.h"
#include "global.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Địa chỉ I2C thường là 0x27, nếu không chạy bạn thử đổi thành 0x3F
LiquidCrystal_I2C lcd(0x27, 16, 2);

void taskLCD_Execution(void *pvParameters) {
  Wire.begin(I2C_SDA, I2C_SCL);
  lcd.init();
  lcd.backlight();

  int toggleView = 0;

  while(1) {
    lcd.clear();
    
    // Cứ mỗi 2 giây, LCD sẽ luân phiên hiển thị Thông tin Sensor hoặc Lệnh Control
    if (toggleView < 2) {
      // Hiển thị thông báo điều khiển (từ Keypad/RFID)
      lcd.setCursor(0, 0);
      lcd.print(g_lcdLine1);
      lcd.setCursor(0, 1);
      lcd.print(g_lcdLine2);
    } else {
      // Hiển thị nhiệt độ, độ ẩm
      lcd.setCursor(0, 0);
      lcd.print("T:" + String(g_temp, 1) + "C H:" + String(g_humid, 1) + "%");
      lcd.setCursor(0, 1);
      lcd.print("PIR: ");
      lcd.print(g_isMotion ? "Motion!" : "Clear  ");
    }

    toggleView++;
    if(toggleView > 3) toggleView = 0;

    vTaskDelay(pdMS_TO_TICKS(1000)); // Cập nhật màn hình mỗi 1 giây
  }
}