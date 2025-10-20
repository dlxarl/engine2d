#include "Engine.h"
#include "Color.h"
#include <iostream>
#include <allegro5/allegro_primitives.h>

Engine::Engine(int width, int height, const char* title)
    : renderer(width, height), running(true),
    line(Point2D(50,50), Point2D(200, 200), Color(255, 0, 0)),
    rectangle(Point2D(300, 100), 150, 100, Color(0, 255, 0)),
    circle(Point2D(500, 300), 80, Color(0, 0, 255))
    {
        al_init();
        al_install_keyboard();
        al_install_mouse();

        display = al_create_display(width, height);
        eventQueue = al_create_event_queue();
        timer = al_create_timer(1.0/ 60.0);

        al_register_event_source(eventQueue, al_get_display_event_source(display));
        al_register_event_source(eventQueue, al_get_timer_event_source(timer));
        al_register_event_source(eventQueue, al_get_keyboard_event_source());
        al_register_event_source(eventQueue, al_get_mouse_event_source());
        
        al_start_timer(timer);
    }

Engine::~Engine() {
    if (timer) al_destroy_timer(timer);
    if (eventQueue) al_destroy_event_queue(eventQueue);
    if (display) al_destroy_display(display);
    al_uninstall_system();
}

void Engine::handleEvents() {
    ALLEGRO_EVENT ev;
    while (al_get_next_event(eventQueue, &ev)) {
        input.handleEvent(ev);

        if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            running = false;

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN &&
            ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
            running = false;
    }
}

void Engine::update(){
    circle.center.x = input.mouseX;
    circle.center.y = input.mouseY;
}

void Engine::render() {
    renderer.clear(Color(0, 0, 0));
    line.draw(renderer);
    rectangle.draw(renderer);
    circle.draw(renderer);
    renderer.drawFramebuffer();
}

void Engine::run() {
    while(running){
        handleEvents();
        update();
        render();
    }
}
