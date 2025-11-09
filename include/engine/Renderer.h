#pragma once
#include <vector>
#include <allegro5/allegro.h>
#include "Color.h"

class Renderer {
public:
    Renderer(int w, int h);
    ~Renderer();

    void clear(Color c);
    void setPixel(int x, int y, Color c);
    void drawFramebuffer(); // запис у texture + один al_draw_bitmap

    ALLEGRO_DISPLAY* getDisplay() const { return display; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

private:
    int width = 0;
    int height = 0;
    std::vector<Color> framebuffer;
    ALLEGRO_DISPLAY* display = nullptr;
    ALLEGRO_BITMAP* texture = nullptr; // offscreen bitmap
};