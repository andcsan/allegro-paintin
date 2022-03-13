#include "application.h"
#include "global.h"

int color;

void drawCircleOnLine(BITMAP *bmp, int x, int y, int d) {
    circlefill(bmp, x, y, d, color);
}

Application::Application() {
    color = 0;
    size = 5;
}

void Application::init() {
    allegro_init();
    install_timer();
    install_keyboard();
    install_mouse();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, APP_WIDTH, APP_HEIGHT, 0, 0);
    set_window_title(APP_NAME);
}

void Application::end() {
    allegro_exit();
}

void Application::update(BITMAP *buff, BITMAP *button_plus, BITMAP *button_minus) {
    if (key[KEY_PLUS_PAD])
        size++;
    if (key[KEY_MINUS_PAD])
        if (size > 0)
            size--;
    if (key[KEY_SPACE])
        clear_to_color(buff, makecol(255, 255, 255));
    if (key[KEY_1_PAD])
        color = RED;
    if (key[KEY_2_PAD])
        color = BLUE;
    if (key[KEY_3_PAD])
        color = GREEN;
    if (key[KEY_4_PAD])
        color = BLACK;
    if (key[KEY_0_PAD])
        color = WHITE;

    if (mouse_z < last_mz) {
        size -= 5;
        if (size < 0) {
            size = 0;
        }
    } else if (mouse_z > last_mz) {
        size += 5;
    }

    last_mz = mouse_z;

    masked_blit(button_plus, buff, 0, 0, APP_WIDTH - 32, 0, 32, 32);

    if (mouse_x > APP_WIDTH - 32 && mouse_x < APP_WIDTH) {
        if (mouse_y > 0 && mouse_y < 32) {
            masked_blit(button_plus, buff, 32, 0, APP_WIDTH - 32, 0, 32, 32);
            if (mouse_b & 1) { size++; }
        }
    } else {
        if (mouse_b & 1) {
            do_line(buff, mouse_x, mouse_y, last_mx, last_my, size, drawCircleOnLine);
        }
        last_mx = mouse_x;
        last_my = mouse_y;
    }


    masked_blit(button_minus, buff, 0, 0, APP_WIDTH - 32, 32, 32, 32);

    if (mouse_x > APP_WIDTH - 32 && mouse_x < APP_WIDTH) {
        if (mouse_y > 32 && mouse_y < 64) {
            masked_blit(button_minus, buff, 32, 0, APP_WIDTH - 32, 32, 32, 32);
            if (mouse_b & 1) {
                size--;
                if (size < 0)
                    size = 0;
            }
        }
    } else {
        if (mouse_b & 1) {
            do_line(buff, mouse_x, mouse_y, last_mx, last_my, size, drawCircleOnLine);
        }
        last_mx = mouse_x;
        last_my = mouse_y;
    }

    textprintf_ex(buff, font, 10, APP_HEIGHT-90, BLACK, WHITE, "+ / -  : Tamanho");
    textprintf_ex(buff, font, 10, APP_HEIGHT-80, BLACK, WHITE, "ESPACO : Resetar");
    textprintf_ex(buff, font, 10, APP_HEIGHT-60, BLACK, WHITE, "0 : Borracha");
    textprintf_ex(buff, font, 10, APP_HEIGHT-50, BLACK, WHITE, "4 : Preto");
    textprintf_ex(buff, font, 10, APP_HEIGHT-40, BLACK, WHITE, "1 : Vermelho");
    textprintf_ex(buff, font, 10, APP_HEIGHT-30, BLACK, WHITE, "2 : Azul");
    textprintf_ex(buff, font, 10, APP_HEIGHT-20, BLACK, WHITE, "3 : Verde");
    textprintf_ex(buff, font, 10, 10, BLACK, WHITE, "%d", color);
    textprintf_ex(buff, font, 10, 20, BLACK, WHITE, "%d", mouse_x);
    textprintf_ex(buff, font, 10, 30, BLACK, WHITE, "%d", mouse_y);
    textprintf_ex(buff, font, 10, 40, BLACK, WHITE, "%d", size);

    show_mouse(NULL);
    draw_sprite(screen, buff, 0, 0);
    circle(screen, mouse_x, mouse_y, size, color);
    show_mouse(screen);
}