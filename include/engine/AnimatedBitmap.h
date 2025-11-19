#pragma once
#include "Shape.h"
#include "Point2D.h"
#include "Renderer.h"
#include <allegro5/allegro.h>
#include <string>
#include <vector>

/**
 * @struct Pixel
 * @brief Struktura reprezentująca pojedynczy piksel w bitmapie.
 *
 * Zawiera wartości koloru w formacie RGBA.
 */
struct Pixel {
    unsigned char r; ///< Składowa koloru czerwonego (0–255)
    unsigned char g; ///< Składowa koloru zielonego (0–255)
    unsigned char b; ///< Składowa koloru niebieskiego (0–255)
    unsigned char a; ///< Składowa kanału alfa (przezroczystość 0–255)
};

/**
 * @class AnimatedBitmap
 * @brief Klasa reprezentująca animowaną bitmapę opartą na sprite sheet.
 *
 * Klasa umożliwia ładowanie arkuszy sprite'ów (sprite sheet),
 * zarządzanie klatkami animacji, skalowaniem oraz odtwarzaniem.
 * Dziedziczy po klasie Shape, dzięki czemu może być rysowana
 * za pomocą renderer’a tak jak inne prymitywy.
 */
class AnimatedBitmap : public Shape {
public:
    ALLEGRO_BITMAP* spriteSheet = nullptr; ///< Wskaźnik do arkusza sprite'ów Allegro
    Point2D position;                      ///< Pozycja bitmapy w przestrzeni 2D

    int frameWidth;    ///< Szerokość pojedynczej klatki animacji
    int frameHeight;   ///< Wysokość pojedynczej klatki animacji
    int totalFrames;   ///< Całkowita liczba klatek animacji
    int currentFrame = 0; ///< Aktualnie wyświetlana klatka

    float frameDuration;  ///< Czas wyświetlania jednej klatki animacji
    float frameTimer = 0.0f; ///< Timer używany do zmiany klatek animacji

    float scale = 1.0f; ///< Skala wyświetlanej bitmapy

    std::vector<Pixel> pixels; ///< Bufor pikseli (do ewentualnych modyfikacji kolorów)

    /**
     * @brief Konstruktor ładujący sprite sheet i ustawiający parametry animacji.
     *
     * @param path Ścieżka do pliku bitmapy (sprite sheet)
     * @param fw Szerokość jednej klatki
     * @param fh Wysokość jednej klatki
     * @param frames Liczba klatek animacji w sprite sheet
     * @param duration Czas trwania jednej klatki
     * @param pos Pozycja początkowa animacji
     * @param sc Skala wyświetlanej bitmapy
     */
    AnimatedBitmap(const std::string& path,
                   int fw, int fh,
                   int frames,
                   float duration,
                   Point2D pos,
                   float sc = 1.0f);

    /**
     * @brief Destruktor zwalniający pamięć zajmowaną przez bitmapę.
     */
    ~AnimatedBitmap();

    /**
     * @brief Aktualizuje animację na podstawie czasu delta.
     *
     * Metoda odpowiada za przełączanie klatek animacji, jeśli tryb
     * odtwarzania jest aktywny.
     *
     * @param deltaTime Czas, jaki upłynął od ostatniej aktualizacji (sekundy)
     */
    void update(float deltaTime);

    /**
     * @brief Rysuje aktualną klatkę animacji za pomocą renderera.
     *
     * @param r Obiekt klasy Renderer odpowiedzialny za rysowanie
     */
    void draw(Renderer& r) override;

    /**
     * @brief Rozpoczyna odtwarzanie animacji.
     *
     * @param looped Określa, czy animacja powinna się zapętlać
     */
    void play(bool looped = true) { playing = true; loop = looped; }

    /**
     * @brief Zatrzymuje animację.
     */
    void stop() { playing = false; }

    /**
     * @brief Ustawia numer aktualnej klatki animacji.
     *
     * Jeśli numer jest spoza zakresu, zostanie zignorowany.
     *
     * @param frame Indeks klatki (0 ≤ frame < totalFrames)
     */
    void setFrame(int frame) {
        if (frame >= 0 && frame < totalFrames)
            currentFrame = frame;
    }

private:
    bool playing = false; ///< Czy animacja jest obecnie odtwarzana
    bool loop = false;    ///< Czy animacja ma być zapętlona
};
