#include "global.h"

// Đây là nơi cấp phát bộ nhớ thực sự cho các biến
volatile float g_temp = 0.0;
volatile float g_humid = 0.0;
volatile bool g_isMotion = false;

volatile bool g_ledState = false;
volatile bool g_fanState = false;
volatile bool g_doorState = false;

String g_lcdLine1 = "Smart Home MVP";
String g_lcdLine2 = "Starting...";

Servo doorServo;