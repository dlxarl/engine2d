#include "Renderer.h"
#include <allegro5/allegro.h>
#include <iostream>

Renderer::Renderer(int w, int h)
    : width(w), height(h), framebuffer(w * h) {
    display = al_create_display(width, height);
    if (!display) {
        std::cerr << "[Renderer] Failed to create display!" << std::endl;
    }
}

void Renderer::clear(Color c) {
    std::fill(framebuffer.begin(), framebuffer.end(), c);
}

void Renderer::setPixel(int x, int y, Color c) {
    if (x < 0 || y < 0 || x >= width || y >= height) return;
    framebuffer[y * width + x] = c;
}

void Renderer::drawFramebuffer() {
    ALLEGRO_BITMAP* back = al_get_backbuffer(display); // ← використовує локальний display
    al_lock_bitmap(back, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            Color col = framebuffer[y * width + x];
            al_put_pixel(x, y, al_map_rgb(col.r, col.g, col.b));
        }
    }

    al_unlock_bitmap(back);
    al_flip_display();
}

ALLEGRO_DISPLAY* Renderer::getDisplay() const {
    return display;
}