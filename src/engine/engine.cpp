#include "include/engine/engine.hpp"

Engine::Engine(int width, int height) : display(nullptr), event_queue(nullptr), timer(nullptr), running(false), screenWidth(width), screenHeight(height) {}
Engine::~Engine() {
    if (timer) al_destroy_timer(timer);
    if (event_queue) al_destroy_event_queue(event_queue);
    if (display) al_destroy_display(display);
}

bool Engine::init() {
    al_init();
    al_install_keyboard();
    al_install_mouse();
    al_init_image_addon();

    display = al_create_display(800, 600);

    event_queue = al_create_event_queue();
    timer = al_create_timer(1.0 / 60);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());
    al_register_event_source(event_queue, al_get_timer_event_source(timer));

    running = true;
    return true;
}