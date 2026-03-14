#ifndef __LED_BLINKY__
#define __LED_BLINKY__
#include <Arduino.h>
#include "global.h"
#include "Adafruit_NeoPixel.h"
#define LED_GPIO 48


#define TEMP_LOW 0
#define TEMP_MEDIUM 1
#define TEMP_HIGH 2

void led_blinky(void *pvParameters);


#endif