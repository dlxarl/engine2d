#include "AnimatedBitmap.h"
#include <iostream>

AnimatedBitmap::AnimatedBitmap(const std::string& path, int fw, int fh, int frames, float duration, Point2D pos, float sc)
    : Shape(Color(255, 255, 255)),
      frameWidth(fw),
      frameHeight(fh),
      totalFrames(frames),
      frameDuration(duration),
      position(pos),
      scale(sc)
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
    if (!spriteSheet) {
        std::cerr << "[AnimatedBitmap] spriteSheet is null!" << std::endl;
        return;
    }

    int sheetWidth = al_get_bitmap_width(spriteSheet);
    if (sheetWidth <= 0 || frameWidth <= 0 || frameHeight <= 0) {
        std::cerr << "[AnimatedBitmap] Invalid frame dimensions!" << std::endl;
        return;
    }

    int columns = sheetWidth / frameWidth;
    if (columns == 0) {
        std::cerr << "[AnimatedBitmap] No columns in sprite sheet!" << std::endl;
        return;
    }

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
                for (int dy = 0; dy < scale; ++dy) {
                    for (int dx = 0; dx < scale; ++dx) {
                        r.setPixel(position.x + x * scale + dx, position.y + y * scale + dy, Color(rC, gC, bC));
                    }
                }
            }
        }
    }
}