#include <Arduino.h>
#include "config.h"
#include "global.h"
#include "task_mock.h"
#include "task_lcd.h"
#include "task_keypad.h"
//#include "task_rfid.h"
#include "task_iot.h"
//#include "light.h"
//#include "door.h"
#include "temp_humid_task.h"
#include "task_pir.h"
#include "device.h"

void setup() {
  Serial.begin(115200);
  
  // Khởi tạo phần cứng dùng chung (Servo)
  // ESP32Servo cần cấp phát timer trước khi attach chân
  doorServo.attach(SERVO_PIN, 544, 2400); // Gắn servo vào chân
  doorServo.write(0); // Đảm bảo cửa ĐÓNG khi khởi động 

  Serial.println("--- KHOI DONG HE THONG RTOS ---");

  // KHỞI TẠO CÁC TASK (Hàm xTaskCreate)
  // Cú pháp: xTaskCreate(Tên_Hàm, Tên_Hiển_Thị, Kích_Thước_RAM, Tham_Số, Độ_Ưu_Tiên, Handle)
  // Stack (RAM) cần lớn đối với các tác vụ liên quan đến Mạng (WiFi/MQTT) và String.

  //xTaskCreate(taskMock_Execution,   "MockTask",   2048, NULL, 2, NULL); // Ưu tiên thấp nhất
  xTaskCreate(taskLCD_Execution,    "LCDTask",    4096, NULL, 2, NULL); 
  xTaskCreate(taskKeypad_Execution, "KeypadTask", 2048, NULL, 2, NULL); // Ưu tiên trung bình
  //xTaskCreate(taskRFID_Execution,   "RFIDTask",   4096, NULL, 4, NULL); // Ưu tiên cao (để không miss thẻ)
  xTaskCreate(taskIoT_Execution,    "IoTTask",    8192, NULL, 5, NULL); // Cần RAM rất lớn cho WiFi
  //xTaskCreate(light_task,           "LightTask",  2048, NULL, 2, NULL); // Ưu tiên trung bình
  //xTaskCreate(door_task,            "DoorTask",   2048, NULL, 3, NULL); // Ưu tiên cao (để phản hồi nhanh)
  xTaskCreate(temp_humid_task,      "TempHumidTask", 4096, NULL, 2, NULL); // Cần RAM cho DHT20
  xTaskCreate(taskPIR_Execution,    "PIRTask",    2048, NULL, 3, NULL); // Ưu tiên cao (để phản hồi nhanh)
  xTaskCreate(device_task,          "DeviceTask", 2048, NULL, 4, NULL); // Ưu tiên cao nhất (điều khiển phần cứng)
}

void loop() {
  
}