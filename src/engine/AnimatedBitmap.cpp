#include "AnimatedBitmap.h"
#include <iostream>
#include <vector>
#include <allegro5/allegro.h>

/**
 * @brief Konstruktor klasy AnimatedBitmap.
 *
 * Wczytuje arkusz sprite'ów z pliku, inicjalizuje parametry animacji
 * oraz przygotowuje tablicę pikseli do ręcznego rysowania.
 *
 * @param path Ścieżka do pliku z arkuszem sprite'ów
 * @param fw Szerokość pojedynczej klatki
 * @param fh Wysokość pojedynczej klatki
 * @param frames Liczba klatek w animacji
 * @param duration Czas trwania jednej klatki w sekundach
 * @param pos Pozycja animowanego bitmapy w przestrzeni 2D
 * @param sc Skala rysowania (domyślnie 1.0)
 */
AnimatedBitmap::AnimatedBitmap(const std::string& path, int fw, int fh, int frames,
                               float duration, Point2D pos, float sc)
    : Shape(Color(255, 255, 255)),
      frameWidth(fw),
      frameHeight(fh),
      totalFrames(frames),
      frameDuration(duration),
      position(pos),
      scale(sc),
      frameTimer(0.0f),
      currentFrame(0)
{
    spriteSheet = al_load_bitmap(path.c_str());
    if (!spriteSheet) {
        std::cerr << "Failed to load sprite sheet: " << path << std::endl;
        return;
    }

    // Pobranie rozmiaru bitmapy
    int sheetWidth = al_get_bitmap_width(spriteSheet);
    int sheetHeight = al_get_bitmap_height(spriteSheet);

    // Zablokowanie bitmapy do odczytu pikseli
    ALLEGRO_LOCKED_REGION* lr = al_lock_bitmap(spriteSheet, ALLEGRO_PIXEL_FORMAT_ABGR_8888, ALLEGRO_LOCK_READONLY);
    if (!lr) {
        std::cerr << "Failed to lock sprite sheet!" << std::endl;
        return;
    }

    uint8_t* base = reinterpret_cast<uint8_t*>(lr->data);
    int pitch = lr->pitch;

    pixels.resize(sheetWidth * sheetHeight);

    // Kopiowanie pikseli z bitmapy do własnej tablicy Pixel
    for (int y = 0; y < sheetHeight; ++y) {
        uint32_t* row = reinterpret_cast<uint32_t*>(base + y * pitch);
        for (int x = 0; x < sheetWidth; ++x) {
            uint32_t argb = row[x];
            uint8_t a = (argb >> 24) & 0xFF;
            uint8_t r = (argb >> 0) & 0xFF;
            uint8_t g = (argb >> 8) & 0xFF;
            uint8_t b = (argb >> 16) & 0xFF;
            pixels[y * sheetWidth + x] = {r, g, b, a};
        }
    }

    al_unlock_bitmap(spriteSheet);
}

/**
 * @brief Destruktor klasy AnimatedBitmap.
 *
 * Zwalnia pamięć bitmapy Allegro.
 */
AnimatedBitmap::~AnimatedBitmap() {
    if (spriteSheet) {
        al_destroy_bitmap(spriteSheet);
    }
}

/**
 * @brief Aktualizuje animację.
 *
 * Zwiększa licznik czasu klatki, zmienia aktualną klatkę w zależności
 * od czasu i ustawień pętli.
 *
 * @param deltaTime Czas, który upłynął od ostatniej aktualizacji (w sekundach)
 */
void AnimatedBitmap::update(float deltaTime) {
    if (!playing) return;

    frameTimer += deltaTime;
    if (frameTimer >= frameDuration) {
        frameTimer = 0.0f;
        currentFrame++;
        if (currentFrame >= totalFrames) {
            if (loop) currentFrame = 0;
            else {
                currentFrame = totalFrames - 1;
                playing = false;
            }
        }
    }
}

/**
 * @brief Rysuje aktualną klatkę animacji na ekranie.
 *
 * Rysuje piksel po pikselu do bufora renderera, uwzględniając przezroczystość
 * oraz skalowanie.
 *
 * @param r Obiekt Renderer używany do rysowania pikseli
 */
void AnimatedBitmap::draw(Renderer& r) {
    if (pixels.empty()) return;

    int sheetWidth = al_get_bitmap_width(spriteSheet);
    int columns = sheetWidth / frameWidth;
    if (columns == 0) return;

    int row = currentFrame / columns;
    int col = currentFrame % columns;

    int srcX = col * frameWidth;
    int srcY = row * frameHeight;

    for (int y = 0; y < frameHeight; ++y) {
        for (int x = 0; x < frameWidth; ++x) {
            const auto& px = pixels[(srcY + y) * sheetWidth + (srcX + x)];
            if (px.a > 0) { // pomijanie przezroczystych pikseli
                for (int dy = 0; dy < scale; ++dy) {
                    for (int dx = 0; dx < scale; ++dx) {
                        r.setPixel(position.x + x * scale + dx,
                                   position.y + y * scale + dy,
                                   Color(px.r, px.g, px.b));
                    }
                }
            }
        }
    }
}
