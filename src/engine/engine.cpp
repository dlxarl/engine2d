#include "Engine.h"
#include <iostream>
#include <allegro5/allegro_primitives.h>

Engine::Engine(int width, int height, float fps)
    : screenWidth(width), screenHeight(height), frameRate(fps),
      display(nullptr), eventQueue(nullptr), timer(nullptr),
      running(false) {}

Engine::~Engine() {
    if (timer) al_destroy_timer(timer);
    if (eventQueue) al_destroy_event_queue(eventQueue);
    if (display) al_destroy_display(display);
    al_uninstall_system();
}

bool Engine::init() {
    if (!al_init()) return false;

    al_install_keyboard();
    al_install_mouse();
    al_init_primitives_addon();

    display = al_create_display(screenWidth, screenHeight);
    if (!display) return false;

    timer = al_create_timer(1.0 / frameRate);
    eventQueue = al_create_event_queue();

    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_mouse_event_source());

    running = true;
    al_start_timer(timer);

    return true;
}

void Engine::run() {
    while (running) {
        handleEvents();
        render();
    }
}

void Engine::stop() { running = false; }

void Engine::handleEvents() {
    ALLEGRO_EVENT ev;
    while (al_get_next_event(eventQueue, &ev)) {
        input.handleEvent(ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            stop();

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
            ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            stop();
    }
}

void Engine::render() {
    renderer.begin();

    for (auto shape : shapes)
        shape->draw();

    // Візуалізація положення миші:
    al_draw_filled_circle(input.mouseX, input.mouseY, 5, al_map_rgb(255, 255, 0));

    renderer.end();
}

void Engine::addShape(Shape* shape) {
    shapes.push_back(shape);
}
