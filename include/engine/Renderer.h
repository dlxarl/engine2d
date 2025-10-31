#pragma once
#include <vector>
#include <allegro5/display.h>
#include "Color.h"

class Renderer {
private:
    int width, height;
    std::vector<Color> framebuffer;
    ALLEGRO_DISPLAY* display; // ← додано

public:
    Renderer(int w, int h);
    void clear(Color c);
    void setPixel(int x, int y, Color c);
    void drawFramebuffer();
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    ALLEGRO_DISPLAY* getDisplay() const; // ← доступ до дисплея
};