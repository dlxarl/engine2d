#pragma once
#include "scenes/headers/Scene.h"

/**
 * @brief Klasa zarządzająca scenami gry.
 *
 * SceneManager odpowiada za przechowywanie aktualnej sceny,
 * jej aktualizację, rysowanie oraz przejście do kolejnej sceny,
 * gdy obecna zostanie zakończona.
 */
class SceneManager {
private:
    Scene* current = nullptr; /**< Wskaźnik na bieżącą scenę */

public:
    /**
     * @brief Konstruktor klasy SceneManager.
     *
     * Inicjalizuje menedżera scen i ustawia początkową scenę.
     *
     * @param startScene Wskaźnik na scenę startową
     */
    SceneManager(Scene* startScene);

    /**
     * @brief Destruktor klasy SceneManager.
     *
     * Zwalnia pamięć zajmowaną przez aktualną scenę.
     */
    ~SceneManager();

    /**
     * @brief Aktualizuje obecną scenę.
     *
     * Wywołuje funkcję update() bieżącej sceny z podanym czasem delta
     * oraz wejściem użytkownika. Jeśli scena jest zakończona,
     * przechodzi do następnej sceny i usuwa obecną.
     *
     * @param deltaTime Czas delta od ostatniej aktualizacji (w sekundach)
     * @param input Obiekt Input do obsługi klawiatury i myszy
     */
    void update(float deltaTime, const Input& input);

    /**
     * @brief Rysuje bieżącą scenę.
     *
     * Wywołuje funkcję draw() obecnej sceny, jeśli scena istnieje.
     *
     * @param r Obiekt Renderer do rysowania sceny
     */
    void draw(Renderer& r);

    /**
     * @brief Sprawdza, czy menedżer scen wciąż działa.
     *
     * @return true jeśli istnieje aktualna scena, false jeśli menedżer nie ma scen do wyświetlenia
     */
    bool isRunning() const;
};

/**
 * @brief Aktualizacja sceny (funkcja globalna).
 */
void update(float deltaTime, const Input& input);
