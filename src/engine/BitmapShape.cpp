#include "BitmapShape.h"
#include <allegro5/allegro_image.h>
#include <iostream>

/**
 * @brief Konstruktor klasy BitmapShape.
 *
 * Wczytuje bitmapę z pliku i ustawia pozycję obiektu.
 * Jeśli wczytanie bitmapy się nie powiedzie, używa koloru zastępczego.
 *
 * @param path Ścieżka do pliku bitmapy
 * @param pos Pozycja bitmapy w przestrzeni 2D
 * @param fallbackColor Kolor zastępczy w przypadku błędu wczytania
 */
BitmapShape::BitmapShape(const std::string& path, Point2D pos, Color fallbackColor)
    : Shape(fallbackColor), position(pos) {
    bitmap = al_load_bitmap(path.c_str());
    if (!bitmap) {
        std::cerr << "Failed to load bitmap: " << path << std::endl;
    }
}

/**
 * @brief Destruktor klasy BitmapShape.
 *
 * Zwalnia pamięć zajętą przez bitmapę Allegro.
 */
BitmapShape::~BitmapShape() {
    if (bitmap) {
        al_destroy_bitmap(bitmap);
    }
}

/**
 * @brief Rysuje bitmapę w przestrzeni 2D.
 *
 * Rysuje piksel po pikselu do bufora renderera, uwzględniając przezroczystość pikseli.
 *
 * @param r Obiekt Renderer używany do rysowania pikseli
 */
void BitmapShape::draw(Renderer& r) {
    if (!bitmap) {
        std::cerr << "[BitmapShape] bitmap is null!" << std::endl;
        return;
    }

    int bmpW = al_get_bitmap_width(bitmap);
    int bmpH = al_get_bitmap_height(bitmap);

    ALLEGRO_LOCKED_REGION* region = al_lock_bitmap(bitmap, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
    if (!region) {
        std::cerr << "[BitmapShape] Failed to lock bitmap!" << std::endl;
        return;
    }

    for (int y = 0; y < bmpH; ++y) {
        for (int x = 0; x < bmpW; ++x) {
            ALLEGRO_COLOR alColor = al_get_pixel(bitmap, x, y);
            unsigned char rC, gC, bC, aC;
            al_unmap_rgba(alColor, &rC, &gC, &bC, &aC);

            if (aC > 0) { // pomijanie przezroczystych pikseli
                r.setPixel(position.x + x, position.y + y, Color(rC, gC, bC));
            }
        }
    }

    al_unlock_bitmap(bitmap);
}
