/**
 * @mainpage SILNIK 2D - Dokumentacja
 *
 * @section intro Wprowadzenie
 * Projekt "SILNIK 2D" to silnik graficzny 2D stworzony w C++ z użyciem biblioteki Allegro5.
 * Celem projektu jest stworzenie podstawowego środowiska do rysowania prymitywów, animacji i obsługi scen.
 * Demo technologiczne pokazuje możliwości silnika i jego funkcje.
 *
 * @section authors Autorzy
 * - Oleksandr Liapun
 * - Andrii Kropyvskyi
 * - Illia Zinchuk
 *
 * @section version Wersja
 * 1.0
 *
 * @section requirements Wymagania i funkcjonalności
 * - Obsługa klawiatury i myszy
 * - Obsługa współrzędnych 2D (Point2D)
 * - Rysowanie prymitywów (linie, okręgi, prostokąty, trójkąty)
 * - Wypełnianie prymitywów kolorem
 * - Przekształcenia geometryczne (skalowanie, obrót, przesunięcie)
 * - Hierarchia klas i obiektowość
 * - Obsługa bitmap i animowanie ich
 * - Demo technologiczne do prezentacji i obrony projektu
 *
 * @section usage Użytkowanie
 * Pliki źródłowe projektu znajdują się w katalogu `src/` lub `scenes/headers/`.
 * Aby uruchomić demo, należy skompilować projekt z Allegro5 i uruchomić główny plik `main.cpp`.
 */


#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <iostream>
#include <filesystem>
#include "Renderer.h"
#include "Input.h"
#include "SceneManager.h"
#include "scenes/headers/Scene1.h"
#include "scenes/headers/SlotGame.h"

/**
 * @brief Główna funkcja programu.
 *
 * Inicjalizuje bibliotekę Allegro 5, dodatki graficzne, obsługę klawiatury i myszy,
 * tworzy obiekty Renderer i Input, a następnie uruchamia główną pętlę gry.
 * W pętli głównej przetwarzane są zdarzenia, aktualizowane sceny, rysowane
 * obiekty i obsługiwane wejścia użytkownika.
 *
 * @param argc Liczba argumentów wiersza poleceń (nieużywane)
 * @param argv Tablica argumentów wiersza poleceń (nieużywane)
 * @return int Kod zakończenia programu (0 = sukces, -1 = błąd inicjalizacji Allegro)
 */
int main(int argc, char** argv) {
    (void)argc; /**< Ignorowanie nieużywanego parametru */
    (void)argv; /**< Ignorowanie nieużywanego parametru */

    // Inicjalizacja biblioteki Allegro
    if (!al_init()) {
        std::cerr << "Nie udało się zainicjalizować Allegro!" << std::endl;
        return -1;
    }

    // Inicjalizacja dodatków Allegro
    al_init_image_addon();       /**< Dodatek do obsługi obrazów (bitmapy) */
    al_init_primitives_addon();  /**< Dodatek do rysowania prymitywów (linie, kształty) */
    al_init_font_addon();        /**< Dodatek do obsługi fontów */
    al_init_ttf_addon();         /**< Dodatek do obsługi fontów TrueType */
    al_install_keyboard();       /**< Instalacja obsługi klawiatury */
    al_install_mouse();          /**< Instalacja obsługi myszy */

    // Wyświetlenie bieżącego katalogu roboczego
    std::cout << "Bieżący katalog roboczy: " << std::filesystem::current_path() << std::endl;

    // Tworzenie obiektu Renderer i Input
    Renderer renderer(800, 600); /**< Obiekt Renderer odpowiedzialny za rysowanie */
    Input input;                 /**< Obiekt Input obsługujący klawiaturę i mysz */

    // Ustawienie tytułu okna
    al_set_window_title(renderer.getDisplay(), "Slot Machine Game");

    // Tworzenie kolejki zdarzeń i timera
    ALLEGRO_EVENT_QUEUE* eventQueue = al_create_event_queue(); /**< Kolejka zdarzeń Allegro */
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);        /**< Timer odświeżania 60 FPS */

    // Rejestracja źródeł zdarzeń
    al_register_event_source(eventQueue, al_get_display_event_source(renderer.getDisplay()));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_mouse_event_source());
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));

    // Uruchomienie timera
    al_start_timer(timer);

    // Tworzenie menedżera scen
    //SceneManager manager(new SlotGame()); /**< Alternatywnie uruchomienie SlotGame */
    SceneManager manager(new Scene1());     /**< Domyślna scena startowa */

    bool running = true; /**< Flaga głównej pętli programu */

    // Główna pętla gry
    while (running && manager.isRunning()) {
        ALLEGRO_EVENT ev;
        while (al_get_next_event(eventQueue, &ev)) {
            input.handleEvent(ev); /**< Obsługa zdarzeń wejścia */

            // Zamknięcie okna
            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                running = false;
        }

        // Wyjście z gry po naciśnięciu ESC
        if (input.isKeyPressed(ALLEGRO_KEY_ESCAPE))
            running = false;

        // Aktualizacja scen
        manager.update(1.0f / 60.0f, input);

        // Czyszczenie ekranu
        renderer.clear(Color(0, 0, 0));

        // Rysowanie sceny
        if (manager.isRunning())
            manager.draw(renderer);

        // Renderowanie bufora na ekran
        renderer.drawFramebuffer();

        // Aktualizacja stanu wejścia
        input.update();
    }

    // Czyszczenie zasobów Allegro
    al_destroy_timer(timer);
    al_destroy_event_queue(eventQueue);

    return 0; /**< Zwraca 0 - sukces */
}
