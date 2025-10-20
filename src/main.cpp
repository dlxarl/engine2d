#include "Engine.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <cmath>

int main() {
    // Ініціалізація рушія
    Engine engine(800, 600, "2D Engine Full Demo");

    Renderer renderer(800, 600);
    Input input;

    // Створюємо об’єкти
    LineShape line(Point2D(100, 100), Point2D(700, 100), Color(255, 0, 0));
    RectangleShape rect(Point2D(300, 200), 150, 100, Color(0, 255, 0));
    CircleShape circle(Point2D(400, 400), 80, Color(0, 0, 255));

    // Allegro для подій
    ALLEGRO_EVENT_QUEUE* eventQueue = al_create_event_queue();
    ALLEGRO_DISPLAY* display = al_create_display(800, 600);
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);

    al_install_keyboard();
    al_install_mouse();

    al_register_event_source(eventQueue, al_get_display_event_source(display));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    al_register_event_source(eventQueue, al_get_mouse_event_source());
    al_register_event_source(eventQueue, al_get_timer_event_source(timer));

    al_start_timer(timer);

    bool running = true;
    float rectSpeed = 2.0f;
    float lineMove = 0;

    while (running) {
        ALLEGRO_EVENT ev;
        while (al_get_next_event(eventQueue, &ev)) {
            input.handleEvent(ev);

            if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
                running = false;
        }

        // --- Оновлення стану ---
        if (input.isKeyPressed(ALLEGRO_KEY_ESCAPE))
            running = false;

        // Переміщення прямокутника клавішами
        if (input.isKeyPressed(ALLEGRO_KEY_LEFT))
            rect.pos.x -= rectSpeed;
        if (input.isKeyPressed(ALLEGRO_KEY_RIGHT))
            rect.pos.x += rectSpeed;
        if (input.isKeyPressed(ALLEGRO_KEY_UP))
            rect.pos.y -= rectSpeed;
        if (input.isKeyPressed(ALLEGRO_KEY_DOWN))
            rect.pos.y += rectSpeed;
            
        // Рух лінії синусом
        //line.p1.y = 100 + sin(lineMove) * 30;
        //line.p2.y = 100 + sin(lineMove) * 30;
        //lineMove += 0.05f;
        

        // Коло рухається за мишею
        circle.center.x = input.mouseX;
        circle.center.y = input.mouseY;

        // --- Рендеринг ---
        renderer.clear(Color(0, 0, 0));  // очищення екрану
        line.draw(renderer);
        rect.draw(renderer);
        circle.draw(renderer);
        renderer.drawFramebuffer();
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(eventQueue);
    al_destroy_display(display);
    return 0;
}
