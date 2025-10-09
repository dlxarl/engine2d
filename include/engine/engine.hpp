#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_keyboard.h>
#include <allegro5/allegro_mouse.h>

class Engine {
private:
    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* event_queue;
    ALLEGRO_TIMER* timer;

    bool running;

    int screenWidth;
    int screenHeight;

public:
    Engine(int width = 800, int height = 600);
    ~Engine();
    
    bool init();
    void run();
    void handleInput(ALLEGRO_EVENT&ev);
    void update(float dt);
    void draw();
    void stop() {running = false;}
};

#endif