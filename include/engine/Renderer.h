#pragma once
#include <vector>
#include "Color.h"

class Renderer {
private:
    int width, height;
    std::vector<Color> framebuffer;

public:
    Renderer(int w, int h);
    void clear(Color c);
    void setPixel(int x, int y, Color c);
    void drawFramebuffer();
    int getWidth() const {return width; }
    int getHeight() const {return height; }
};
