#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"
#include "hardware/i2c.h"
#include "hardware/clocks.h"
#include "ssd1306.h"

#define LED_RED 12
#define LED_GREEN 11
#define LED_BLUE 13
#define BUTTON_A 5
#define JOYSTICK_X 26
#define JOYSTICK_Y 27
#define JOYSTICK_BTN 22
#define I2C_SDA 14
#define I2C_SCL 15
#define I2C_PORT i2c1
#define I2C_ADDRESS 0x3C
#define PWM_MAX 255
#define PWM_FREQ 20000
#define DISPLAY_WIDTH 128
#define DISPLAY_HEIGHT 64
#define DISPLAY_SDA 14
#define DISPLAY_SCL 15
#define TEMPO_DEBOUNCE 200
#define VALOR_CENTRAL 2048

ssd1306_t display;
uint32_t ultimo_tempo = 0;

volatile bool led_B_ativado = 0; 
volatile bool led_G_ativado = 0;
volatile bool led_R_ativado = 0;
volatile bool BUTTON_A_pressionado = false;
volatile int valor_x; 
volatile int valor_y;
volatile uint16_t adc_valor_x;
volatile uint16_t adc_valor_y; 
bool pintar = true;
uint slice_r;
uint slice_b;

void callback_botao(uint gpio, uint32_t events);
void setup();
uint16_t calcular_pwm(int valor_adc);
void movimento_vermelho_x();
void movimento_azul_y();


int main()
{
    setup();
    
    int x = 63;
    int y = 31; 

    gpio_set_irq_enabled_with_callback(BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &callback_botao);
    gpio_set_irq_enabled_with_callback(JOYSTICK_BTN, GPIO_IRQ_EDGE_FALL, true, &callback_botao);

    while (true) {

        movimento_vermelho_x();
        movimento_azul_y();

        ssd1306_fill(&display, !pintar);

        if(led_G_ativado){
            ssd1306_rect(&display, 1, 1, 126, 62, pintar, !pintar); 
        }

        //eixo x
        if(adc_valor_y == 2048){
            x = 63;
        }
        else if (adc_valor_y > 2048){
            x = ((adc_valor_y - 2048) / 32) + 54;
        }
        else{
            x = (((adc_valor_y - 2048)) / 32) + 67;
        }
        
        // eixo y
        if(adc_valor_x == 2048)
            y = 31;
        else if(adc_valor_x > 2048){
            y =  67 - (adc_valor_x / 64);
        }
        else{
            y = 54 - ((adc_valor_x) / 64);
        }

        ssd1306_rect(&display, 3, 3, 122, 60, pintar, !pintar);
        ssd1306_rect(&display, y, x, 8, 8, pintar, pintar);         
        ssd1306_send_data(&display); 

        sleep_ms(100);
    }
}

void setup() {

    stdio_init_all();

    //LEDS
    gpio_init(LED_RED);
    gpio_init(LED_GREEN);
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    
    gpio_set_function(LED_RED, GPIO_FUNC_PWM);
    gpio_set_function(LED_BLUE, GPIO_FUNC_PWM);

    slice_r = pwm_gpio_to_slice_num(LED_RED);
    slice_b = pwm_gpio_to_slice_num(LED_BLUE);
    pwm_set_clkdiv(slice_r, (float)clock_get_hz(clk_sys) / PWM_FREQ / (PWM_MAX + 1));
    pwm_set_clkdiv(slice_b, (float)clock_get_hz(clk_sys) / PWM_FREQ / (PWM_MAX + 1));
    pwm_set_wrap(slice_r, PWM_MAX);
    pwm_set_wrap(slice_b, PWM_MAX);
    pwm_set_enabled(slice_r, true);
    pwm_set_enabled(slice_b, true);
    led_R_ativado = 1;
    led_B_ativado = 1;

    
    //DISPLAY
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(DISPLAY_SDA, GPIO_FUNC_I2C);                    
    gpio_set_function(DISPLAY_SCL, GPIO_FUNC_I2C);                    
    gpio_pull_up(DISPLAY_SDA);                                        
    gpio_pull_up(DISPLAY_SCL);                                      
    ssd1306_init(&display, DISPLAY_WIDTH, DISPLAY_HEIGHT, false, I2C_ADDRESS, I2C_PORT); 
    ssd1306_config(&display);                                              
    ssd1306_send_data(&display);  
    ssd1306_rect(&display, 31, 63, 8, 8, pintar, !pintar);
    ssd1306_send_data(&display);

    //JOYSTICK
    adc_init();
    adc_gpio_init(JOYSTICK_X);
    adc_gpio_init(JOYSTICK_Y);

    //botao
    gpio_init(BUTTON_A);
    gpio_set_dir(BUTTON_A, GPIO_IN);
    gpio_pull_up(BUTTON_A);

    gpio_init(JOYSTICK_BTN);
    gpio_set_dir(JOYSTICK_BTN, GPIO_IN);
    gpio_pull_up(JOYSTICK_BTN);
}

void callback_botao(uint gpio, uint32_t events) {
    uint32_t tempo_atual = to_ms_since_boot(get_absolute_time());

    if (tempo_atual - ultimo_tempo >= TEMPO_DEBOUNCE) {
        if(gpio == BUTTON_A) {
            led_R_ativado = !led_R_ativado;
            led_B_ativado = !led_B_ativado;
            pwm_set_enabled(slice_r, led_R_ativado); 
            pwm_set_enabled(slice_b, led_B_ativado); 
        }        
        else if(gpio == JOYSTICK_BTN){
            led_G_ativado = !led_G_ativado;
            gpio_put(LED_GREEN, led_G_ativado);
        }
    
    ultimo_tempo = tempo_atual;
    }
}

void movimento_vermelho_x(){
    adc_select_input(0);
    adc_valor_x = adc_read();
    printf("ADC X: %d\n", adc_read());
    sleep_us(10);

    pwm_set_gpio_level(LED_RED, calcular_pwm(adc_valor_x));  
}

void movimento_azul_y(){
    adc_select_input(1);
    adc_valor_y = adc_read();
    printf("ADC Y: %d\n", adc_read());
    sleep_us(10);

    pwm_set_gpio_level(LED_BLUE, calcular_pwm(adc_valor_y));  
}

uint16_t calcular_pwm(int valor_adc) {
    return (uint16_t)((abs(valor_adc - VALOR_CENTRAL) * PWM_MAX) / VALOR_CENTRAL);
}
