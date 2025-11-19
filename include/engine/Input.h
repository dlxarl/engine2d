#pragma once
#include <allegro5/allegro.h>

/**
 * @class Input
 * @brief Klasa obsługująca wejście użytkownika (klawiatura i mysz) w Allegro 5.
 *
 * Rejestruje stany klawiszy i przycisków myszy, umożliwia sprawdzenie
 * czy klawisz/przycisk jest wciśnięty lub został właśnie wciśnięty.
 */
class Input {
public:
    bool keys[ALLEGRO_KEY_MAX] = { false };          ///< Aktualny stan wszystkich klawiszy
    bool previousKeys[ALLEGRO_KEY_MAX] = { false };  ///< Stan klawiszy w poprzedniej aktualizacji

    bool mouseButtons[5] = { false };               ///< Aktualny stan przycisków myszy (0–4)
    bool previousMouseButtons[5] = { false };       ///< Stan przycisków myszy w poprzedniej aktualizacji

    float mouseX = 0, mouseY = 0;                   ///< Aktualna pozycja kursora myszy

    /**
     * @brief Obsługuje zdarzenia wejściowe z Allegro.
     *
     * Metoda aktualizuje stany klawiszy i przycisków myszy na podstawie zdarzenia.
     *
     * @param ev Zdarzenie Allegro do obsłużenia
     */
    void handleEvent(ALLEGRO_EVENT& ev);

    /**
     * @brief Aktualizuje stany klawiszy i przycisków myszy.
     *
     * Należy wywoływać w każdej iteracji pętli głównej gry/aplikacji.
     */
    void update();

    /**
     * @brief Sprawdza, czy dany klawisz jest wciśnięty.
     *
     * @param key Kod klawisza (ALLEGRO_KEY_*)
     * @return true jeśli klawisz jest wciśnięty, false jeśli nie
     */
    bool isKeyPressed(int key) const;

    /**
     * @brief Sprawdza, czy dany klawisz został właśnie wciśnięty.
     *
     * @param keycode Kod klawisza (ALLEGRO_KEY_*)
     * @return true jeśli klawisz został właśnie wciśnięty, false w przeciwnym wypadku
     */
    bool isKeyJustPressed(int keycode) const;

    /**
     * @brief Sprawdza, czy przycisk myszy jest wciśnięty.
     *
     * @param button Numer przycisku myszy (0–4)
     * @return true jeśli przycisk jest wciśnięty, false jeśli nie
     */
    bool isMousePressed(int button) const;

    /**
     * @brief Sprawdza, czy przycisk myszy został właśnie wciśnięty.
     *
     * @param button Numer przycisku myszy (0–4)
     * @return true jeśli przycisk został właśnie wciśnięty, false w przeciwnym wypadku
     */
    bool isMouseJustPressed(int button) const;
};
