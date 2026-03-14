#include "task_rfid.h"
#include "config.h"
#include "global.h"
#include <SPI.h>
#include <MFRC522.h>

MFRC522 rfid(RFID_SS, RFID_RST);

void taskRFID_Execution(void *pvParameters) {
  // Khởi tạo SPI với các chân đã định nghĩa cho ESP32-S3
  SPI.begin(RFID_SCK, RFID_MISO, RFID_MOSI, RFID_SS);
  rfid.PCD_Init();
  Serial.println("RFID Ready!");

  while(1) {
    // Nếu có thẻ mới và đọc thành công
    if (rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
      String uidString = "";
      for (byte i = 0; i < rfid.uid.size; i++) {
        uidString += String(rfid.uid.uidByte[i] < 0x10 ? "0" : "");
        uidString += String(rfid.uid.uidByte[i], HEX);
      }
      uidString.toUpperCase();
      
      Serial.println("Card UID: " + uidString);

      // Mở cửa và cập nhật LCD
      g_doorState = true;
      doorServo.write(90);
      g_lcdLine1 = "Door Opened!";
      g_lcdLine2 = "ID: " + uidString;

      // Dừng đọc thẻ hiện tại
      rfid.PICC_HaltA();
      rfid.PCD_StopCrypto1();

      // Giữ trạng thái cửa mở 3 giây rồi cho phép quét tiếp
      vTaskDelay(pdMS_TO_TICKS(3000));
      
      // Tự động đóng cửa lại (Tuỳ chọn)
      // g_doorState = false;
      // doorServo.write(0);
    }
    
    // Quét thẻ mỗi 100ms
    vTaskDelay(pdMS_TO_TICKS(100));
  }
}