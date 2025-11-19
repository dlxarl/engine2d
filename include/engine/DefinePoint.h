#pragma once
#include "Input.h"
#include <iostream>

/**
 * @class DefinePoint
 * @brief Klasa służąca do definiowania punktów na ekranie za pomocą myszy.
 *
 * Umożliwia włączenie/wyłączenie rejestrowania kliknięć myszy oraz wypisywanie
 * współrzędnych kliknięcia w konsoli.
 */
class DefinePoint {
private:
    bool enabled = false; ///< Flaga określająca, czy rejestrowanie punktów jest aktywne

public:
    /**
     * @brief Ustawia, czy klasa ma być aktywna.
     *
     * @param state true włącza rejestrowanie kliknięć, false wyłącza
     */
    void setEnabled(bool state) { enabled = state; }

    /**
     * @brief Sprawdza, czy rejestrowanie punktów jest aktywne.
     *
     * @return true jeśli włączone, false jeśli wyłączone
     */
    bool isEnabled() const { return enabled; }

    /**
     * @brief Aktualizuje stan punktu na podstawie wejścia myszy.
     *
     * Jeśli klasa jest włączona i wykryto kliknięcie lewym przyciskiem myszy,
     * wypisuje współrzędne kliknięcia w konsoli.
     *
     * @param input Obiekt klasy Input zawierający informacje o stanie myszy i klawiatury
     */
    void update(const Input& input) {
        if (!enabled) return;

        if (input.isMouseJustPressed(0)) {
            std::cout << "Clicked at: ("
                      << input.mouseX << ", "
                      << input.mouseY << ")" << std::endl;
        }
    }
};
