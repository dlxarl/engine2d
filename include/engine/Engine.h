#pragma once
#include <allegro5/allegro.h>
#include "Input.h"
#include "Renderer.h"
#include "LineShape.h"
#include <CircleShape.h>
#include <RectangleShape.h>


class Engine {
public:
    Engine(int width, int height, const char* title);
    ~Engine();

    void run();

private:
    

    bool running;
    int screenWidth, screenHeight;
    float frameRate;

    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* eventQueue;
    ALLEGRO_TIMER* timer;

    LineShape line;
    CircleShape circle;
    RectangleShape rectangle;

    Input input;
    Renderer renderer;
    
    void handleEvents();
    void update();
    void render();
};
