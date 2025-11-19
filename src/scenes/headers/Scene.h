#pragma once
#include "Renderer.h"
#include "Input.h"

/**
 * @brief Klasa bazowa dla scen w silniku 2D.
 *
 * Reprezentuje pojedynczą scenę lub stan gry/aplikacji.
 * Każda scena powinna implementować aktualizację logiki oraz rysowanie.
 */
class Scene {
public:
    /**
     * @brief Wirtualny destruktor.
     *
     * Zapewnia poprawne niszczenie klas pochodnych.
     */
    virtual ~Scene() = default;

    /**
     * @brief Aktualizuje logikę sceny.
     *
     * @param deltaTime Czas, jaki upłynął od ostatniej aktualizacji (w sekundach)
     * @param input Obiekt klasy Input do obsługi klawiatury i myszy
     */
    virtual void update(float deltaTime, const Input& input) = 0;

    /**
     * @brief Rysuje scenę na podanym rendererze.
     *
     * @param r Obiekt Renderer używany do rysowania pikseli
     */
    virtual void draw(Renderer& r) = 0;

    /**
     * @brief Sprawdza, czy scena zakończyła działanie.
     *
     * @return true jeśli scena jest zakończona, false w przeciwnym wypadku
     */
    virtual bool isFinished() const { return false; }

    /**
     * @brief Zwraca wskaźnik na następną scenę.
     *
     * @return Wskaźnik na nową scenę lub nullptr jeśli nie ma następnej
     */
    virtual Scene* nextScene() const { return nullptr; }
};
