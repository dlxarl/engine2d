#include "BitmapShape.h"
#include <allegro5/allegro_image.h>
#include <iostream>

BitmapShape::BitmapShape(const std::string& path, Point2D pos, Color fallbackColor)
    : Shape(fallbackColor), position(pos) {
    bitmap = al_load_bitmap(path.c_str());
    if (!bitmap) {
        std::cerr << "Failed to load bitmap: " << path << std::endl;
    }
}

BitmapShape::~BitmapShape() {
    if (bitmap) {
        al_destroy_bitmap(bitmap);
    }
}

void BitmapShape::draw(Renderer& r) {
    if (bitmap) {
        al_draw_bitmap(bitmap, position.x, position.y, 0);
    } else {
        // Якщо зображення не завантажилось — малюємо кольоровий квадрат
        al_draw_filled_rectangle(position.x, position.y,
                                 position.x + 100, position.y + 100,
                                 al_map_rgb(color.r, color.g, color.b));
    }
}