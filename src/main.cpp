#include "Engine.h"
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
#include "scenes/headers/SnakeGame.h"

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    // Allegro core initialization
    if (!al_init()) {
        std::cerr << "Failed to initialize Allegro!" << std::endl;
        return -1;
    }

    // Addons
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_install_mouse();

    std::cout << "Current working dir: " << std::filesystem::current_path() << std::endl;

    // Renderer creates display internally
    Renderer renderer(800, 600);
    Input input;

    // Event system
    ALLEGRO_EVENT_QUEUE* eventQueue = al_create_event_queue();
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    // Register event sources
    al_register_event_source(eventQueue, al_get_display_event_source(renderer.getDisplay()));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_mouse_event_source());
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    // Scene manager with initial scene
    SceneManager manager(new Scene1());

    bool running = true;

    while (running && manager.isRunning()) {
        ALLEGRO_EVENT ev;
        while (al_get_next_event(eventQueue, &ev)) {
            input.handleEvent(ev);

            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                running = false;
        }

        if (input.isKeyPressed(ALLEGRO_KEY_ESCAPE))
            running = false;

        // Update and render current scene
        manager.update(1.0f / 60.0f, input);
        renderer.clear(Color(0, 0, 0));

        if (manager.isRunning())
            manager.draw(renderer);

        renderer.drawFramebuffer();
        input.update();
    }

    // Cleanup
    al_destroy_timer(timer);
    al_destroy_event_queue(eventQueue);
    return 0;
}