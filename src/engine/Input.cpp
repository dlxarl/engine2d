#include "Input.h"

/**
 * @brief Obsługuje zdarzenia wejściowe Allegro.
 *
 * Aktualizuje stany klawiszy oraz przycisków myszy w zależności od rodzaju zdarzenia.
 *
 * @param ev Zdarzenie Allegro typu ALLEGRO_EVENT
 */
void Input::handleEvent(ALLEGRO_EVENT& ev) {
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        keys[ev.keyboard.keycode] = true;
    else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        keys[ev.keyboard.keycode] = false;
    else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
        mouseX = ev.mouse.x;
        mouseY = ev.mouse.y;
    } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        mouseButtons[ev.mouse.button - 1] = true;
    else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        mouseButtons[ev.mouse.button - 1] = false;
}

/**
 * @brief Aktualizuje stany poprzednich klawiszy i przycisków myszy.
 *
 * Funkcja powinna być wywoływana na końcu każdej klatki gry,
 * aby umożliwić wykrycie zdarzeń "just pressed".
 */
void Input::update() {
    for (int i = 0; i < ALLEGRO_KEY_MAX; ++i) {
        previousKeys[i] = keys[i];
    }
    for (int i = 0; i < 5; ++i) {
        previousMouseButtons[i] = mouseButtons[i];
    }
}

/**
 * @brief Sprawdza, czy dany klawisz jest aktualnie wciśnięty.
 *
 * @param key Kod klawisza (ALLEGRO_KEY_*)
 * @return true jeśli klawisz jest wciśnięty, false w przeciwnym wypadku
 */
bool Input::isKeyPressed(int key) const {
    return keys[key];
}

/**
 * @brief Sprawdza, czy klawisz został właśnie wciśnięty (tylko w tej klatce).
 *
 * @param keycode Kod klawisza (ALLEGRO_KEY_*)
 * @return true jeśli klawisz został wciśnięty w tej klatce
 */
bool Input::isKeyJustPressed(int keycode) const {
    return keys[keycode] && !previousKeys[keycode];
}

/**
 * @brief Sprawdza, czy przycisk myszy jest aktualnie wciśnięty.
 *
 * @param button Numer przycisku myszy (0-4)
 * @return true jeśli przycisk jest wciśnięty
 */
bool Input::isMousePressed(int button) const {
    return mouseButtons[button];
}

/**
 * @brief Sprawdza, czy przycisk myszy został właśnie wciśnięty (tylko w tej klatce).
 *
 * @param button Numer przycisku myszy (0-4)
 * @return true jeśli przycisk został wciśnięty w tej klatce
 */
bool Input::isMouseJustPressed(int button) const {
    return mouseButtons[button] && !previousMouseButtons[button];
}
