#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"


#define LED_PIN GPIO_NUM_13        // LED pin
#define BUTTON_PIN GPIO_NUM_4      // button pin

bool bstatememory = false;   // Button state (true = pressed, false = not pressed)
bool pressed;          // Flag to indicate a button press event
bool lstate = false;   // LED state (false = off, true = on)
bool blink = false;   // blink mode (off = don't blink, on = blink)

void app_main(void) {
    // TO-DO: Configure LED output
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_pullup_dis(LED_PIN);
    gpio_pulldown_dis(LED_PIN);
    gpio_intr_disable(LED_PIN);
    gpio_set_level(LED_PIN, 0);

    // TO-DO: Configure BUTTON input
    gpio_reset_pin(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_pullup_en(BUTTON_PIN);

    while (1) {
        // TO-DO: Implement LED toggle and button logic here
        pressed = gpio_get_level(BUTTON_PIN) == 0;     // Input active low button

        if (!bstatememory && pressed) {            // Released button, is now pressed
            bstatememory = true;                   // Remember button is pressed  
        }
    
        if (bstatememory && !pressed) {            // Pressed button, is now released
            blink = !blink;                        // Toggle LED state  
            bstatememory = false;                 // Remember button is released
        }
        
        //implementing blink logic

        if (blink) {                            //if blink mode is set to on
            //blink
            if (!lstate) {                         //if led was off
                gpio_set_level(LED_PIN, 1);        //turn LED on
                lstate = !lstate;                  // indicate that LED was turned on
                vTaskDelay(500 / portTICK_PERIOD_MS);
            } else {                              //if led was on
                gpio_set_level(LED_PIN, 0);        //turn LED off
                lstate = !lstate;                  // indicate that LED was turned off
                vTaskDelay(500 / portTICK_PERIOD_MS);
            }
        } else {                                //if blink mode is set to off
            gpio_set_level(LED_PIN, blink);       // LED turns off
        }
        vTaskDelay(25 / portTICK_PERIOD_MS);      // loop delay (button debounce delay measure)
   }
}