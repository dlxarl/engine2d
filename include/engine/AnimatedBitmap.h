#pragma once
#include "Shape.h"
#include "Point2D.h"
#include <allegro5/allegro.h>
#include <string>
#include <vector>

// Простий контейнер для кольору з альфою
struct Pixel {
    unsigned char r, g, b, a;
};

class AnimatedBitmap : public Shape {
public:
    ALLEGRO_BITMAP* spriteSheet = nullptr;
    Point2D position;

    int frameWidth;
    int frameHeight;
    int totalFrames;
    int currentFrame = 0;

    float frameDuration; // тривалість одного кадру
    float frameTimer = 0.0f;

    float scale = 1.0f;

    // CPU‑буфер для пікселів спрайт‑аркуша
    std::vector<Pixel> pixels;

    AnimatedBitmap(const std::string& path, int fw, int fh, int frames,
                   float duration, Point2D pos, float sc = 1.0f);
    ~AnimatedBitmap();

    void update(float deltaTime);
    void draw(Renderer& r) override;
};
