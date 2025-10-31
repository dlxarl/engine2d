#include "Engine.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <filesystem>

#include "Renderer.h"
#include "Input.h"
#include "SceneManager.h"
#include "scenes/headers/Scene1.h"

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    // Engine initialization
    Engine engine(800, 600, "2D Engine Full Demo");

    std::cout << "Current working dir: " << std::filesystem::current_path() << std::endl;

    Renderer renderer(800, 600);
    Input input;

    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();

    // Allegro event setup
    ALLEGRO_EVENT_QUEUE* eventQueue = al_create_event_queue();
    ALLEGRO_DISPLAY* display = al_create_display(800, 600);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    al_register_event_source(eventQueue, al_get_display_event_source(display));
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

    al_destroy_timer(timer);
    al_destroy_event_queue(eventQueue);
    al_destroy_display(display);
    return 0;
}