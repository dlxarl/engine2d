#pragma once
#include <allegro5/allegro.h>

class Input {
public:
    bool keys[ALLEGRO_KEY_MAX] = { false };
    bool previousKeys[ALLEGRO_KEY_MAX] = { false };

    bool mouseButtons[5] = { false };
    float mouseX = 0, mouseY = 0;

    void handleEvent(ALLEGRO_EVENT& ev);
    void update();
    bool isKeyPressed(int key) const;
    bool isMousePressed(int button);
    bool isKeyJustPressed(int keycode) const;
};