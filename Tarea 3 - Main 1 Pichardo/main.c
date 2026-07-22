#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

// Pines 
#define LED_GPIO 4        
#define BTN_GPIO 2        

// Estados de la máquina
typedef enum {
    LED_APAGADO,
    LED_ENCENDIDO
} led_state_t;

led_state_t estado_actual = LED_APAGADO;

void app_main(void) {
    // Configuración del LED
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    // Configuración del botón
    gpio_reset_pin(BTN_GPIO);
    gpio_set_direction(BTN_GPIO, GPIO_MODE_INPUT);
    gpio_pullup_en(BTN_GPIO);

    while (1) {
        // Leer el botón
        int valor_boton = gpio_get_level(BTN_GPIO);

        if (valor_boton == 0) { // Botón presionado
            estado_actual = (estado_actual == LED_APAGADO) ? LED_ENCENDIDO : LED_APAGADO;
            vTaskDelay(pdMS_TO_TICKS(250)); // Anti-rebote
        }

        // Actualizar LED según estado
        gpio_set_level(LED_GPIO, (estado_actual == LED_ENCENDIDO) ? 1 : 0);

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
