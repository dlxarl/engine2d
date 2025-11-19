#include "Renderer.h"
#include <allegro5/allegro.h>
#include <algorithm>
#include <cstdint>
#include <iostream>

Renderer::Renderer(int w, int h)
    : width(w), height(h), framebuffer(static_cast<size_t>(w) * static_cast<size_t>(h)) {

    al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
    display = al_create_display(width, height);
    if (!display) {
        std::cerr << "[Renderer] Failed to create display\n";
    }
}

Renderer::~Renderer() {
    if (display) al_destroy_display(display);
}

void Renderer::clear(Color c) {
    std::fill(framebuffer.begin(), framebuffer.end(), c);
}

void Renderer::setPixel(int x, int y, Color c) {
    if (x < 0 || y < 0 || x >= width || y >= height) return;
    framebuffer[static_cast<size_t>(y) * static_cast<size_t>(width) + static_cast<size_t>(x)] = c;
}

void Renderer::drawFramebuffer() {
    if (!display) return;


    ALLEGRO_BITMAP* back = al_get_backbuffer(display);
    ALLEGRO_LOCKED_REGION* lr = al_lock_bitmap(back, ALLEGRO_PIXEL_FORMAT_ABGR_8888, ALLEGRO_LOCK_WRITEONLY);
    if (!lr) {
        std::cerr << "[Renderer] Failed to lock backbuffer\n";
        return;
    }

    uint8_t* base = reinterpret_cast<uint8_t*>(lr->data);
    int pitch = lr->pitch;

    auto norm = [](float v) -> float {
        if (v > 1.0f) v /= 255.0f;
        return std::clamp(v, 0.0f, 1.0f);
    };

    for (int y = 0; y < height; ++y) {
        uint32_t* row = reinterpret_cast<uint32_t*>(base + y * pitch);
        size_t off = static_cast<size_t>(y) * static_cast<size_t>(width);
        for (int x = 0; x < width; ++x) {
            const Color& c = framebuffer[off + x];
            uint8_t r8 = static_cast<uint8_t>(norm(c.r) * 255.0f + 0.5f);
            uint8_t g8 = static_cast<uint8_t>(norm(c.g) * 255.0f + 0.5f);
            uint8_t b8 = static_cast<uint8_t>(norm(c.b) * 255.0f + 0.5f);
            uint8_t a8 = 255;
            row[x] = (uint32_t(a8) << 24) | (uint32_t(b8) << 16) | (uint32_t(g8) << 8) | uint32_t(r8);
        }
    }

    al_unlock_bitmap(back);
    al_flip_display();
}