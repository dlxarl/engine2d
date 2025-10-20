#pragma once
#include <allegro5/allegro.h>

class Input {
public:
    bool keys[ALLEGRO_KEY_MAX] = { false };
    bool mouseButtons[5] = { false };
    float mouseX = 0, mouseY = 0;

    void handleEvent(ALLEGRO_EVENT& ev);
    bool isKeyPressed(int key);
    bool isMousePressed(int button);
};
