#include "func/quadrado.h"

extern int pos_x;
extern int pos_y;


void quadrado() {
    adc_select_input(0);
    x_value = adc_read();

    adc_select_input(1);
    y_value = adc_read();

    pwm_red = joystick_to_pwm(y_value);
    pwm_blue = joystick_to_pwm(x_value);

    // Atualiza as variáveis globais pos_x e pos_y com base no valor do joystick
    pos_x = centro_x + ((2048 - (int)x_value) * centro_x) / 2048;
    pos_y = centro_y - ((2048 - (int)y_value) * centro_y) / 2048;

    // Desenha o quadrado na tela com as novas posições
    ssd1306_fill(&ssd, false);
    desenhar_borda();
    ssd1306_rect(&ssd, pos_x, pos_y, square_size, square_size, true, true);
    ssd1306_send_data(&ssd);
}
