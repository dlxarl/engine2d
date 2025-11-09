#include "Renderer.h"
#include <allegro5/allegro.h>
#include <algorithm>
#include <cstdint>
#include <iostream>

Renderer::Renderer(int w, int h)
    : width(w), height(h), framebuffer(static_cast<size_t>(w) * static_cast<size_t>(h)) {
    // Спробуємо увімкнути VSync (побажання) перед створенням дисплея
    al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
    display = al_create_display(width, height);
    if (!display) {
        std::cerr << "[Renderer] Failed to create display\n";
    }
    texture = al_create_bitmap(width, height);
    if (!texture) {
        std::cerr << "[Renderer] Failed to create offscreen bitmap\n";
    }
}

Renderer::~Renderer() {
    if (texture) al_destroy_bitmap(texture);
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
    if (!display || !texture) return;

    // Записуємо у texture (один раз за кадр) — швидше, ніж al_put_pixel на бек-буфері
    ALLEGRO_LOCKED_REGION* lr = al_lock_bitmap(texture, ALLEGRO_PIXEL_FORMAT_ABGR_8888, ALLEGRO_LOCK_WRITEONLY);
    if (!lr) {
        // fallback: якщо не змогли заблокувати — очистити і flip
        al_set_target_backbuffer(display);
        al_clear_to_color(al_map_rgb(0,0,0));
        al_flip_display();
        return;
    }

    uint8_t* base = reinterpret_cast<uint8_t*>(lr->data);
    int pitch = lr->pitch;

    auto norm = [](float v)->float {
        // Якщо значення в 0..255 діапазоні — нормалізуємо, інакше вважаємо 0..1
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

    al_unlock_bitmap(texture);

    // Малюємо texture один раз на бек-буфер і фліп
    al_set_target_backbuffer(display);
    al_clear_to_color(al_map_rgb(0,0,0));
    al_draw_bitmap(texture, 0, 0, 0);
    al_flip_display();
}

