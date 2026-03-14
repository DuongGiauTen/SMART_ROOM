#include "display_task.h"
#include "Wire.h"
#include <LiquidCrystal_I2C.h>
#include "global.h"

LiquidCrystal_I2C lcd(0x27, 16, 2); 

uint8_t bell[8]  = {0x4,0xe,0xe,0xe,0x1f,0x0,0x4};
uint8_t note[8]  = {0x2,0x3,0x2,0xe,0x1e,0xc,0x0};
uint8_t heart[8] = {0x0,0xa,0x1f,0x1f,0xe,0x4,0x0};
uint8_t duck[8]  = {0x0,0xc,0x1d,0xf,0xf,0x6,0x0};
uint8_t check[8] = {0x0,0x1,0x3,0x16,0x1c,0x8,0x0};
uint8_t cross[8] = {0x0,0x1b,0xe,0x4,0xe,0x1b,0x0};
uint8_t retarrow[8] = {	0x1,0x1,0x5,0x9,0x1f,0x8,0x4};

void display_task(void *pvParameters){
    
    Wire.begin(11, 12);
    lcd.init(); 
    //Wire.begin(11, 12);
    lcd.backlight();
    
    lcd.createChar(0, bell);
    lcd.createChar(1, note);
    lcd.createChar(3, heart);
    lcd.createChar(4, duck);
    lcd.createChar(5, check);
    lcd.createChar(6, cross);
    lcd.createChar(7, retarrow);
    lcd.home();

    while (1){
        switch (systemState) {
            case INITIAL:
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("INITIAL STATE");
                lcd.write(0);
                vTaskDelay(2000); // Giữ trạng thái này trong 2 giây để dễ quan sát
                systemState = LED_CONTROL; // Chuyển sang trạng thái tiếp theo để demo
                break;
            case LED_CONTROL:
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("LED CONTROL");
                lcd.write(1);

                vTaskDelay(2000); // Giữ trạng thái này trong 2 giây để dễ quan sát
                systemState = FAN_CONTROL; // Chuyển sang trạng thái tiếp theo để demo
                break;
            case FAN_CONTROL:
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("FAN CONTROL");
                lcd.write(3);
                vTaskDelay(2000); // Giữ trạng thái này trong 2 giây để dễ quan sát
                systemState = INITIAL; // Chuyển về trạng thái ban đầu để demo vòng lặp

                break;
            default:
                lcd.setCursor(0, 0);
                lcd.print("UNKNOWN STATE");
                vTaskDelay(2000); // Giữ trạng thái này trong 2 giây để dễ quan sát
                systemState = INITIAL; // Chuyển về trạng thái ban đầu để demo vòng l
        }   
    }
}