#include "SceneManager.h"
#include <iostream>

/**
 * @brief Konstruktor klasy SceneManager.
 *
 * Inicjalizuje menedżera scen i ustawia początkową scenę.
 *
 * @param startScene Wskaźnik na scenę startową
 */
SceneManager::SceneManager(Scene* startScene) : current(startScene) {}

/**
 * @brief Destruktor klasy SceneManager.
 *
 * Zwalnia pamięć zajmowaną przez aktualną scenę.
 */
SceneManager::~SceneManager() {
    delete current;
}

/**
 * @brief Aktualizuje obecną scenę.
 *
 * Wywołuje funkcję update() bieżącej sceny z podanym czasem delta
 * oraz wejściem użytkownika. Jeśli scena jest zakończona,
 * przechodzi do następnej sceny i usuwa obecną.
 *
 * @param dt Czas delta od ostatniej aktualizacji (w sekundach)
 * @param input Obiekt Input do obsługi klawiatury i myszy
 */
void SceneManager::update(float dt, const Input& input) {
    if (!current) return;

    current->update(dt, input);

    if (current->isFinished()) {
        Scene* next = current->nextScene(); /**< Pobranie następnej sceny */
        delete current;                     /**< Usunięcie obecnej sceny */
        current = next;

        if (!current) {
            std::cout << "SceneManager: brak następnej sceny, kończenie programu." << std::endl;
            return;
        }
    }
}

/**
 * @brief Rysuje bieżącą scenę.
 *
 * Wywołuje funkcję draw() obecnej sceny, jeśli scena istnieje.
 *
 * @param r Obiekt Renderer do rysowania sceny
 */
void SceneManager::draw(Renderer& r) {
    if (current)
        current->draw(r);
}

/**
 * @brief Sprawdza, czy menedżer scen wciąż działa.
 *
 * @return true jeśli istnieje aktualna scena, false jeśli menedżer nie ma scen do wyświetlenia
 */
bool SceneManager::isRunning() const {
    return current != nullptr;
}
