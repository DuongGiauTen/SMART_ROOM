//#include "main.h"
#include "global.h"


void setup()
{
  Serial.begin(115200);
  delay(2000);

  xTaskCreate(led_blinky, "Task LED Blink", 2048, NULL, 2, NULL);
  xTaskCreate(display_task, "Task Display", 2048, NULL, 2, NULL);
  
}

void loop()
{
  
}