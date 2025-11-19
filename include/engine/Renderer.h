#pragma once
#include <vector>
#include <allegro5/allegro.h>
#include "Color.h"

/**
 * @class Renderer
 * @brief Klasa odpowiedzialna za renderowanie grafiki 2D.
 *
 * Umożliwia rysowanie piksel po pikselu, zarządzanie buforem klatek
 * oraz wyświetlanie zawartości na ekranie za pomocą Allegro 5.
 */
class Renderer {
public:
    /**
     * @brief Konstruktor tworzący renderer o określonej szerokości i wysokości.
     *
     * @param w Szerokość okna/obrazu w pikselach
     * @param h Wysokość okna/obrazu w pikselach
     */
    Renderer(int w, int h);

    /**
     * @brief Destruktor zwalniający zasoby powiązane z renderowaniem.
     */
    ~Renderer();

    /**
     * @brief Czyści bufor klatek określonym kolorem.
     *
     * @param c Kolor, którym zostanie wypełniony bufor
     */
    void clear(Color c);

    /**
     * @brief Ustawia pojedynczy piksel w buforze klatek.
     *
     * @param x Współrzędna X piksela
     * @param y Współrzędna Y piksela
     * @param c Kolor piksela
     */
    void setPixel(int x, int y, Color c);

    /**
     * @brief Rysuje zawartość bufora klatek na ekranie.
     */
    void drawFramebuffer();

    /**
     * @brief Zwraca wskaźnik do aktualnego wyświetlacza Allegro.
     *
     * @return Wskaźnik do ALLEGRO_DISPLAY
     */
    ALLEGRO_DISPLAY* getDisplay() const { return display; }

    /**
     * @brief Zwraca szerokość renderera.
     *
     * @return Szerokość w pikselach
     */
    int getWidth() const { return width; }

    /**
     * @brief Zwraca wysokość renderera.
     *
     * @return Wysokość w pikselach
     */
    int getHeight() const { return height; }

private:
    int width = 0;                  ///< Szerokość renderera w pikselach
    int height = 0;                 ///< Wysokość renderera w pikselach
    std::vector<Color> framebuffer; ///< Bufor klatek przechowujący kolory pikseli
    ALLEGRO_DISPLAY* display = nullptr; ///< Wskaźnik do wyświetlacza Allegro
    ALLEGRO_BITMAP* texture = nullptr;  ///< Bitmapa używana do renderowania bufora
};
