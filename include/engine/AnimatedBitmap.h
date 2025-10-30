#pragma once
#include "Shape.h"
#include "Point2D.h"
#include <allegro5/allegro.h>
#include <string>

class AnimatedBitmap : public Shape {
public:
    ALLEGRO_BITMAP* spriteSheet = nullptr;
    Point2D position;

    int frameWidth;
    int frameHeight;
    int totalFrames;
    int currentFrame = 0;

    float frameDuration; // frame duration
    float frameTimer = 0.0f;

    AnimatedBitmap(const std::string& path, int fw, int fh, int frames, float duration, Point2D pos);
    ~AnimatedBitmap();

    void update(float deltaTime);
    void draw(Renderer& r) override;
};