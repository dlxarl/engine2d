#include "AnimatedBitmap.h"
#include <iostream>

AnimatedBitmap::AnimatedBitmap(const std::string& path, int fw, int fh, int frames, float duration, Point2D pos)
    : Shape(Color(255, 255, 255)), // або будь-який інший колір
      frameWidth(fw),
      frameHeight(fh),
      totalFrames(frames),
      frameDuration(duration),
      position(pos)
{
    spriteSheet = al_load_bitmap(path.c_str());
    if (!spriteSheet) {
        std::cerr << "Failed to load sprite sheet: " << path << std::endl;
    }
}

AnimatedBitmap::~AnimatedBitmap() {
    if (spriteSheet) {
        al_destroy_bitmap(spriteSheet);
    }
}

void AnimatedBitmap::update(float deltaTime) {
    frameTimer += deltaTime;
    if (frameTimer >= frameDuration) {
        frameTimer = 0.0f;
        currentFrame = (currentFrame + 1) % totalFrames;
    }
}

void AnimatedBitmap::draw(Renderer& r) {
    if (!spriteSheet) return;

    int sheetWidth = al_get_bitmap_width(spriteSheet);
    int columns = sheetWidth / frameWidth;

    int row = currentFrame / columns;
    int col = currentFrame % columns;

    int srcX = col * frameWidth;
    int srcY = row * frameHeight;

    for (int y = 0; y < frameHeight; ++y) {
        for (int x = 0; x < frameWidth; ++x) {
            ALLEGRO_COLOR c = al_get_pixel(spriteSheet, srcX + x, srcY + y);
            unsigned char rC, gC, bC, aC;
            al_unmap_rgba(c, &rC, &gC, &bC, &aC);
            if (aC > 0) {
                r.setPixel(position.x + x, position.y + y, Color(rC, gC, bC));
            }
        }
    }
}