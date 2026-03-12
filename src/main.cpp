//#include "main.h"
#include "led_blinky.h"
#include "global.h"


void setup()
{
  Serial.begin(115200);
  xTaskCreate(led_blinky, "Task LED Blink", 2048, NULL, 2, NULL);
  
}

void loop()
{
  
}