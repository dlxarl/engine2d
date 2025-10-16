#pragma once
#include <allegro5/allegro.h>
#include <vector>
#include "Input.h"
#include "Renderer.h"
#include "Shape.h"

class Engine {
public:
    Engine(int width, int height, float fps);
    ~Engine();

    bool init();
    void run();
    void stop();

    void addShape(Shape* shape);

private:
    void handleEvents();
    void render();

    bool running;
    int screenWidth, screenHeight;
    float frameRate;

    ALLEGRO_DISPLAY* display;
    ALLEGRO_EVENT_QUEUE* eventQueue;
    ALLEGRO_TIMER* timer;

    Input input;
    Renderer renderer;
    std::vector<Shape*> shapes;
};
