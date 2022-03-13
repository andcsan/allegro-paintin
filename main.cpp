#include <allegro.h>
#include "application.h"

volatile int timer = 0;
volatile int quit = false;

void increaseTimer() {
    timer++;
} END_OF_FUNCTION(increaseTimer);

void quitApp() {
    quit = true;
} END_OF_FUNCTION(quitApp);

int main()
{
    Application app;
    app.init();

    LOCK_VARIABLE(timer);
    LOCK_FUNCTION(increaseTimer);
    install_int_ex(increaseTimer, BPS_TO_TIMER(60));

    set_close_button_callback(quitApp);

    BITMAP *buffer = NULL;
    BITMAP *plus_button = NULL;
    BITMAP *minus_button = NULL;

    buffer = create_bitmap(640, 480);
    plus_button = load_bitmap("assets/plus.bmp", 0);
    minus_button = load_bitmap("assets/minus.bmp", 0);
    clear_to_color(buffer, makecol(255, 255, 255));

    show_mouse(screen);

    while (!quit) {
        if (timer > 0) {
            timer -= 1;
            app.update(buffer, plus_button, minus_button);
        }
    }

    destroy_bitmap(buffer);
    destroy_bitmap(plus_button);
    destroy_bitmap(minus_button);
    app.end();
    return 0;
} END_OF_MAIN();