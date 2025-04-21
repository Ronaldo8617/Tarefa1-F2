#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "hardware/pio.h"
#include <math.h>
#include "lib/ssd1306.h"
#include "lib/rgb.h"
#include "lib/matrixws.h"
#include "lib/buttons.h"
#include "lib/buzzer.h"
#include "lib/display_init.h"
#include "func/funcionalidades.h"
#include "func/quadrado.h"

// Definições de constantes
#define WIDTH        128       // Largura do display
#define HEIGHT       64        // Altura do display
#define square_size  8         // Tamanho do quadrado rastreado
#define BUZZER_PIN   buzzer    // Pino do buzzer
#define MATRIX_PIN   7         // Pino da matriz de LEDs

// Variáveis globais
volatile bool button_b_pressed = false;  // Flag para botão B pressionado
bool travado = false;                    // Estado de travamento do sistema
int pos_x = 64, pos_y = 32;              // Posição inicial (centro do display)

// Callback para interrupção do botão B (modo toggle)
void gpio_button_callback(uint gpio, uint32_t events) {
    uint32_t now = to_ms_since_boot(get_absolute_time());
    static uint32_t last_b = 0;           // Último tempo de acionamento
    
    if (gpio == BOTAO_B && (now - last_b) > DEBOUNCE_DELAY) {
        last_b = now;                     // Atualiza tempo do último acionamento
        button_b_pressed = true;          // Sinaliza pressionamento
        travado = !travado;               // Alterna estado de travamento
    }
}

// Ativa buzzer como alerta
void buzzer_alerta() {
    buzzer_init(BUZZER_PIN, 1000);       // Inicializa buzzer
    buzzer_set_freq(BUZZER_PIN, 1000);   // Define frequência (1kHz)
    sleep_ms(200);                       // Mantém por 200ms
    buzzer_stop(BUZZER_PIN);             // Desliga buzzer
}

// Aciona matriz de LEDs como alerta (verde)
void matriz_led_alerta() {
    for (int i = 0; i < NUM_LEDS; i++) {
        cores(i, 0, 255, 0);             // Define cor verde para todos LEDs
    }
    bf();                                // Atualiza matriz
}

// Desliga todos LEDs da matriz
void desligar_matriz() {
    desliga();                           // Chama função de desligamento
}

// Verifica se o quadrado está próximo das bordas
bool verificar_borda() {
    bool borda = pos_x <= 5 || pos_x + square_size >= 50 ||
                 pos_y <= 5 || pos_y + square_size >= 120;
    if (borda) {
        printf(" Atingiu a borda!\n");   // Log para debug
    }
    return borda;
}

int main() {
    stdio_init_all();                    // Inicializa stdio (USB)

    // Inicializa hardware
    iniciar_botoes();                    // Configura botões
    gpio_set_irq_enabled_with_callback(BOTAO_B,
        GPIO_IRQ_EDGE_FALL | GPIO_IRQ_EDGE_RISE,
        true, &gpio_button_callback);    // Configura interrupção para botão B
    init_adc_joy();                      // Inicializa ADC para joystick
    iniciar_rgb();                       // Configura LEDs RGB
    display();                           // Inicializa display OLED
    controle(PINO_MATRIZ);               // Configura matriz de LEDs
    pwm_init_gpio(red, BRILHO_MAX);      // Inicializa PWM para LED vermelho
    pwm_init_gpio(blue, BRILHO_MAX);     // Inicializa PWM para LED azul
    buzzer_init(BUZZER_PIN, 1000);       // Teste inicial do buzzer
    sleep_ms(100);
    buzzer_stop(BUZZER_PIN);

    // Loop principal
    while (true) {
        printf("X: %d  Y: %d\n", pos_x, pos_y);  // Log de posição

        if (!travado) {                  // Se sistema não está travado
            quadrado();                  // Atualiza posição do quadrado

            if (verificar_borda()) {    // Verifica colisão com bordas
                buzzer_alerta();        // Ativa alertas sonoro
                matriz_led_alerta();    // Ativa alerta visual (matriz)
                pwm_set_gpio_level(red, 255);    // LED vermelho aceso
                pwm_set_gpio_level(green, 0);
                pwm_set_gpio_level(blue, 0);
            } else {                     // Se não está na borda
                buzzer_stop(BUZZER_PIN); // Desliga alertas
                desligar_matriz();
                pwm_set_gpio_level(red, 0);  // Desliga LED vermelho
            }
        } else {                         // Se sistema travado
            buzzer_stop(BUZZER_PIN);     // Mantém alertas desligados
            desligar_matriz();
            pwm_set_gpio_level(red, 0);
        }

        printf("Posição X: %d, Posição Y: %d\n", pos_x, pos_y);  // Debug
        sleep_ms(100);                   // Delay para evitar flicker
    }

    return 0;
}