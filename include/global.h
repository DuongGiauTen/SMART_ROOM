#ifndef __GLOBAL__
#define __GLOBAL__

#include <Arduino.h>

#include "led_blinky.h"
#include "display_task.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define INITIAL 0
#define LED_CONTROL 1
#define FAN_CONTROL 2

extern uint32_t systemState; // Biến toàn cục để lưu trạng thái hệ thống

#endif // __GLOBAL__