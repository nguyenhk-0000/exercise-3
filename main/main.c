/*
 * Name: Nguyen Hieu Kien
 * Date: 01/19/2026
 * Description: Activity 2 Challenge. This code toggles an LED on every  other press of BUTTON_PIN, but only if BUTTON_PIN2 is also held down
 * Hardware: LED on GPIO 10, Button 1 on GPIO 11, Button 2 on GPIO 12.
 */



#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_10
#define BUTTON_PIN GPIO_NUM_11
#define BUTTON_PIN2 GPIO_NUM_12 

void app_main(void) {
    
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    
    gpio_reset_pin(BUTTON_PIN);
    gpio_set_direction(BUTTON_PIN, GPIO_MODE_INPUT);
    gpio_pullup_en(BUTTON_PIN);
    gpio_pulldown_dis(BUTTON_PIN);

    gpio_reset_pin(BUTTON_PIN2);
    gpio_set_direction(BUTTON_PIN2, GPIO_MODE_INPUT);
    gpio_pullup_en(BUTTON_PIN2);
    gpio_pulldown_dis(BUTTON_PIN2);

    int led_state = 0;
    int last_button_state = 1;

    while (1) {
        //read button state 
        int current_button_state = gpio_get_level(BUTTON_PIN);
        int enable_button_state = gpio_get_level(BUTTON_PIN2);

        
        if (last_button_state == 1 && current_button_state == 0) {
                        	// Debounce
            vTaskDelay(50 / portTICK_PERIOD_MS);
            if (gpio_get_level(BUTTON_PIN) == 0 && enable_button_state == 0) {
                // Toggle state
                led_state = !led_state;
                gpio_set_level(LED_PIN, led_state);
            }
        }
        
        last_button_state = current_button_state;
        vTaskDelay(10 / portTICK_PERIOD_MS); 
    }
}