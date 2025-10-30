#include "Engine.h"
#include <allegro5/allegro.h>
#include <iostream>
#include <allegro5/allegro_image.h>
#include "BitmapShape.h"
#include "TriangleShape.h"
#include <filesystem>
#include "AnimatedBitmap.h"

int main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    // Engine initialization
    Engine engine(800, 600, "2D Engine Full Demo");

    // DEBUG - remove later
    std::cout << "Current working dir: " << std::filesystem::current_path() << std::endl;

    Renderer renderer(800, 600);
    Input input;

    al_init_image_addon();

    // Deploy objects
    LineShape line(Point2D(100, 100), Point2D(700, 100), Color(255, 0, 0));
    RectangleShape rect(Point2D(300, 100), 150, 100, Color(0, 255, 0), Color(0, 0, 0));
    CircleShape circle(Point2D(400, 400), 80, Color(0, 0, 255));
    TriangleShape triangle(Point2D(600, 300), 60, Color(255, 255, 0));
    BitmapShape image("assets/test_static.png", Point2D(400, 300));
    AnimatedBitmap anim("assets/test_anim.png", 130, 130, 4, 0.2f, Point2D(200, 200));

    // Allegro for events
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

        // State update
        if (input.isKeyPressed(ALLEGRO_KEY_ESCAPE))
            running = false;

        if (input.isKeyJustPressed(ALLEGRO_KEY_F)) {
            circle.toggleFill();
        }

        if (input.isKeyJustPressed(ALLEGRO_KEY_T)) {
            triangle.toggleFill();
        }

        // Move rectangle with arrows
        if (input.isKeyPressed(ALLEGRO_KEY_LEFT))
            rect.pos.x -= rectSpeed;
        if (input.isKeyPressed(ALLEGRO_KEY_RIGHT))
            rect.pos.x += rectSpeed;
        if (input.isKeyPressed(ALLEGRO_KEY_UP))
            rect.pos.y -= rectSpeed;
        if (input.isKeyPressed(ALLEGRO_KEY_DOWN))
            rect.pos.y += rectSpeed;
            
        // Line movement
        // line.p1.y = 100 + sin(lineMove) * 30;
        // line.p2.y = 100 + sin(lineMove) * 30;
        // lineMove += 0.05f;
        

        // Circle follows cursor
        circle.center.x = input.mouseX;
        circle.center.y = input.mouseY;

        triangle.update();

        // Rendering
        renderer.clear(Color(0, 0, 0));
        line.draw(renderer);
        rect.draw(renderer);
        circle.draw(renderer);
        triangle.draw(renderer);
        image.draw(renderer);
        anim.update(1.0f / 60.0f); // 60 FPS
        anim.draw(renderer);
        renderer.drawFramebuffer();
        input.update();
    }

    al_destroy_timer(timer);
    al_destroy_event_queue(eventQueue);
    al_destroy_display(display);
    return 0;
}
