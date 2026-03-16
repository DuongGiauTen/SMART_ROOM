#include "task_lcd.h"
#include "config.h"
#include "global.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x21, 16, 2);
LiquidCrystal_I2C lcd2(0x27, 16, 2);

void taskLCD_Execution(void *pvParameters) {
    Wire.begin(I2C_SDA, I2C_SCL);
    lcd.init();
    lcd.backlight();
    lcd2.init();
    lcd2.backlight();
    
    uint32_t LastState = 99;  // Để tránh lcd bị reload quá nhiều
    uint32_t sysLocal;

    lcd.setCursor(2,0);
    lcd.print("Smart Room");
    lcd.setCursor(1,1);
    lcd.print("Manifest Team");
    vTaskDelay(pdMS_TO_TICKS(3000)); 

    while(1) {
        sysLocal = systemState; 

        if (sysLocal != LastState) {
            lcd.clear();
            LastState = sysLocal;
        }

        
        switch (sysLocal) {
            case INITIAL:
                lcd2.setCursor(0,0);
                lcd2.print("Initializing...");
                lcd2.setCursor(0,1);
                lcd2.print("DUONG DEP TRAI");

                lcd.setCursor(0,0);
                lcd.print("T:");
                lcd.print(g_temp, 1); 
                lcd.print("C ");      

                lcd.setCursor(9,0);
                lcd.print("H:");
                lcd.print(g_humid, 1);
                lcd.print("% ");

                lcd.setCursor(0,1);
                lcd.print("PIR:");
                
                if(g_isMotion == true) {
                    lcd.print("Have people "); 
                } else {
                    lcd.print("No people   "); 
                }
                break;

            case LED_CONTROL:
                lcd.setCursor(0,0);
                lcd.print("LED CONTROL     ");
                lcd.setCursor(0,1);
                if (g_ledState == true) {
                    lcd.print("ON              ");
                } else {
                    lcd.print("OFF             ");
                }
                break;

            case FAN_CONTROL:
                lcd.setCursor(0,0);
                lcd.print("FAN CONTROL     ");
                lcd.setCursor(0,1);
                if (g_fanState == true) {
                    lcd.print("ON              ");
                } else {
                    lcd.print("OFF             ");
                }
                break;

            case DOOR_CONTROL:
                lcd.setCursor(0,0);
                lcd.print("DOOR CONTROL    ");
                lcd.setCursor(0,1);
                if (g_doorState == true) {
                    lcd.print("OPEN            ");
                } else {
                    lcd.print("CLOSED          ");
                }
                break;
                
            default:
                break;
        }

        
        vTaskDelay(pdMS_TO_TICKS(200)); 
    }
}