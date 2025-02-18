#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "ssd1306.h"


#define LED_RED 11
#define LED_GREEN 12
#define LED_BLUE 13
#define BUTTON_A 5
#define JOYSTICK_X 26
#define JOYSTICK_Y 27
#define JOYSTICK_BTN 22
#define I2C_SDA 14
#define I2C_SCL 15
#define PWM_MAX 255
#define ADC_MAX 4095
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64

int main()
{
    stdio_init_all();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
