#pragma once
#include "Shape.h"
#include "Point2D.h"
#include <allegro5/allegro.h>
#include <string>

class BitmapShape : public Shape {
public:
    ALLEGRO_BITMAP* bitmap = nullptr;
    Point2D position;

    BitmapShape(const std::string& path, Point2D pos, Color fallbackColor = Color(255, 0, 255));
    ~BitmapShape();

    void draw(Renderer& r) override;
};