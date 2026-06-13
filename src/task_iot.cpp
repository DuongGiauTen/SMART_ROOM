#include "task_iot.h"
#include "config.h"
#include "global.h"
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// --- 1. KHAI BÁO CÁC KÊNH ĐỂ GỬI LÊN (PUBLISH) ---
Adafruit_MQTT_Publish tempFeed   = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish humidFeed  = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");
Adafruit_MQTT_Publish motionFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/motion");

// Dùng thêm Publish cho Led, Fan, Door để đồng bộ trạng thái khi ta bấm Keypad vật lý
Adafruit_MQTT_Publish ledPub     = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/led");
Adafruit_MQTT_Publish fanPub     = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/fan");
Adafruit_MQTT_Publish doorPub    = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/door");

// --- 2. KHAI BÁO CÁC KÊNH ĐỂ LẮNG NGHE LỆNH (SUBSCRIBE) ---
Adafruit_MQTT_Subscribe ledSub   = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/led");
Adafruit_MQTT_Subscribe fanSub   = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/fan");
Adafruit_MQTT_Subscribe doorSub  = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/door");

// Biến lưu thời gian để đếm đủ 10 giây
uint32_t lastPublishTime = 0;

// Biến lưu trạng thái trước đó để chỉ publish khi thay đổi
bool prevLedState = false;
bool prevFanState = false;
bool prevDoorState = false;
bool prevMotionState = false;

// Biến lưu thời gian publish cuối cho temp/humid (mỗi 5 phút)
uint32_t lastTempHumidPublishTime = 0;

// Biến lưu giá trị trước đó cho temp/humid để kiểm tra thay đổi
float prevTemp = 0.0;
float prevHumid = 0.0;

void MQTT_Connect() {
    int8_t ret;
    if (mqtt.connected()) return;

    Serial.print("Connecting to MQTT... ");
    uint8_t retries = 3;
    
    // BẮT BUỘC: Phải đăng ký lắng nghe (Subscribe) TRƯỚC KHI gọi connect()
    

    while ((ret = mqtt.connect()) != 0) { 
        Serial.println(mqtt.connectErrorString(ret));
        Serial.println("Retrying MQTT connection in 5 seconds...");
        mqtt.disconnect();
        vTaskDelay(pdMS_TO_TICKS(5000)); 
        retries--;
        if (retries == 0) return; 
    }
    Serial.println("MQTT Connected!");
}

void taskIoT_Execution(void *pvParameters) {
    Serial.print("Connecting to WiFi");
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED) {
        vTaskDelay(pdMS_TO_TICKS(500));
        Serial.print(".");
    }
    Serial.println("\nWiFi Connected.");

    mqtt.subscribe(&ledSub);
    mqtt.subscribe(&fanSub);
    mqtt.subscribe(&doorSub);

    while(1) {
        MQTT_Connect();

        // -------------------------------------------------------------
        // PHẦN A: LẮNG NGHE LỆNH ĐIỀU KHIỂN TỪ WEB (THỜI GIAN THỰC)
        // -------------------------------------------------------------
        // Hàm readSubscription sẽ đứng chờ 50ms xem có ai bấm nút trên Web không.
        // Nếu có, nó sẽ bắt lấy gói tin đó vào biến 'subscription'
        Adafruit_MQTT_Subscribe *subscription;
        while ((subscription = mqtt.readSubscription(50))) {
            
            // 1. NẾU NHẬN ĐƯỢC LỆNH BẬT/TẮT ĐÈN
            if (subscription == &ledSub) {
                // Ép kiểu chuỗi nhận được thành số nguyên (0 hoặc 1)
                int state = atoi((char *)ledSub.lastread); 
                g_ledState = (state == 1); // Cập nhật biến toàn cục
                systemState = LED_CONTROL; // Đổi màn hình LCD sang Menu LED
                Serial.print("[Web Control] LED is now: ");
                Serial.println(g_ledState ? "ON" : "OFF");
            }
            
            // 2. NẾU NHẬN ĐƯỢC LỆNH BẬT/TẮT QUẠT
            else if (subscription == &fanSub) {
                int state = atoi((char *)fanSub.lastread);
                g_fanState = (state == 1);
                systemState = FAN_CONTROL; // Đổi màn hình LCD
                Serial.print("[Web Control] FAN is now: ");
                Serial.println(g_fanState ? "ON" : "OFF");
            }
            
            // 3. NẾU NHẬN ĐƯỢC LỆNH ĐÓNG/MỞ CỬA
            else if (subscription == &doorSub) {
                int state = atoi((char *)doorSub.lastread);
                g_doorState = (state == 1);
                systemState = DOOR_CONTROL; // Đổi màn hình LCD
                Serial.print("[Web Control] DOOR is now: ");
                Serial.println(g_doorState ? "OPEN" : "CLOSED");
            }
        }

        // -------------------------------------------------------------
        // PHẦN B: GỬI DỮ LIỆU THEO LOGIC TỐI ƯU
        // -------------------------------------------------------------
        // Publish trạng thái chỉ khi thay đổi
        if (g_ledState != prevLedState) {
            if (mqtt.connected()) {
                ledPub.publish(g_ledState ? 1 : 0);
                Serial.println("[IoT] LED state published");
            }
            prevLedState = g_ledState;
        }

        if (g_fanState != prevFanState) {
            if (mqtt.connected()) {
                fanPub.publish(g_fanState ? 1 : 0);
                Serial.println("[IoT] FAN state published");
            }
            prevFanState = g_fanState;
        }

        if (g_doorState != prevDoorState) {
            if (mqtt.connected()) {
                doorPub.publish(g_doorState ? 1 : 0);
                Serial.println("[IoT] DOOR state published");
            }
            prevDoorState = g_doorState;
        }

        if (g_isMotion != prevMotionState) {
            if (mqtt.connected()) {
                motionFeed.publish(g_isMotion ? 1 : 0);
                Serial.println("[IoT] Motion state published");
            }
            prevMotionState = g_isMotion;
        }

        // Publish temp/humid mỗi 5 phút hoặc khi thay đổi đáng kể (>1°C hoặc >5%)
        bool shouldPublishTempHumid = false;
        if (millis() - lastTempHumidPublishTime >= 300000) {  // 5 phút = 300000 ms
            shouldPublishTempHumid = true;
        } else if (abs(g_temp - prevTemp) >= 1.0 || abs(g_humid - prevHumid) >= 5.0) {
            shouldPublishTempHumid = true;
        }

        if (shouldPublishTempHumid && mqtt.connected()) {
            tempFeed.publish(g_temp);
            humidFeed.publish(g_humid);
            Serial.println("[IoT] Temp/Humid published");
            lastTempHumidPublishTime = millis();
            prevTemp = g_temp;
            prevHumid = g_humid;
        }

        static uint32_t lastPingTime = 0;
        if (millis() - lastPingTime > 60000) { 
            if(!mqtt.ping()) {
                Serial.println("[IoT] Ping failed, disconnecting...");
                mqtt.disconnect();
            }
            lastPingTime = millis();
        }

        // Nhường CPU cho task khác một nhịp siêu ngắn để chống treo máy
        vTaskDelay(pdMS_TO_TICKS(10)); 
    }
}