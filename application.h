#ifndef APPLICATION_H
#define APPLICATION_H

#include <allegro.h>

void drawCircleOnLine(BITMAP *bmp, int x, int y, int d);

class Application {
    public:
        Application();
        void init();
        void end();
        void update(BITMAP *buffer, BITMAP *button_plus, BITMAP *button_minus);

    private:
        int last_mx;
        int last_my;
        int last_mz;
        int size;
};

#endif