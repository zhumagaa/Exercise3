#include "freertos/FreeRTOS.h"
#include "driver/gpio.h"


#define LED_PIN GPIO_NUM_14        // LED pin
#define BUTTON_PIN GPIO_NUM_4      // button pin

bool bstatememory = false;   // Button state (true = pressed, false = not pressed)
bool pressed;          // Flag to indicate a button press event
bool lstate = false;   // LED state (false = off, true = on)
int pressCount = 0;     //counter to turn LED every otehr time (every second press)

void app_main(void) {
    // TO-DO: Configure LED output
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
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
            // printf("Button is being pressed!\n");
        }
    
        if (bstatememory && !pressed) {            // Pressed button, is now released
            vTaskDelay(25 / portTICK_PERIOD_MS); // button debounce delay
            
            if (gpio_get_level(BUTTON_PIN) == 1) {
                pressCount++;
                //LED turns on every other (every second) time
                // Client has to press button twice every time to turn the LED on/off

                if (pressCount == 2) {
                    lstate = !lstate;
                    pressCount = 0;
                }
            }
            bstatememory = false;
        }
        
        gpio_set_level(LED_PIN, lstate);          // Output LED state

        vTaskDelay(5 / portTICK_PERIOD_MS);      // loop delay
   }
}