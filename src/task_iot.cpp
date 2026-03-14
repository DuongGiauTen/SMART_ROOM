#include "task_iot.h"
#include "config.h"
#include "global.h"
#include <WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Khai báo các Feeds (Kênh dữ liệu) trên Adafruit IO
Adafruit_MQTT_Publish tempFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/temperature");
Adafruit_MQTT_Publish humidFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/humidity");
Adafruit_MQTT_Publish motionFeed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/motion");

void MQTT_Connect() {
  int8_t ret;
  if (mqtt.connected()) return;

  Serial.print("Connecting to MQTT... ");
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect() trả về 0 nếu thành công
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    vTaskDelay(pdMS_TO_TICKS(5000)); 
    retries--;
    if (retries == 0) return; // Nếu lỗi quá 3 lần thì bỏ qua, lát vòng loop sẽ gọi lại
  }
  Serial.println("MQTT Connected!");
}

void taskIoT_Execution(void *pvParameters) {
  // 1. Kết nối WiFi
  Serial.print("Connecting to WiFi");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    vTaskDelay(pdMS_TO_TICKS(500));
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected.");

  while(1) {
    // 2. Giữ kết nối MQTT
    MQTT_Connect();

    // 3. Đẩy dữ liệu lên Cloud
    if (mqtt.connected()) {
      tempFeed.publish(g_temp);
      humidFeed.publish(g_humid);
      motionFeed.publish(g_isMotion ? 1 : 0);
      Serial.println("Data Published to Adafruit IO!");
    }

    // PING để giữ kết nối không bị văng
    if(!mqtt.ping()) {
      mqtt.disconnect();
    }

    // Đẩy dữ liệu mỗi 10 giây (Tránh bị Adafruit khóa vì gửi quá nhanh)
    vTaskDelay(pdMS_TO_TICKS(10000));
  }
}