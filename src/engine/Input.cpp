#include "Input.h"

void Input::handleEvent(ALLEGRO_EVENT& ev) {
    if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
        keys[ev.keyboard.keycode] = true;
    else if (ev.type == ALLEGRO_EVENT_KEY_UP)
        keys[ev.keyboard.keycode] = false;
    else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES) {
        mouseX = ev.mouse.x;
        mouseY = ev.mouse.y;
    } else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
        mouseButtons[ev.mouse.button - 1] = true;
    else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
        mouseButtons[ev.mouse.button - 1] = false;
}

void Input::update() {
    for (int i = 0; i < ALLEGRO_KEY_MAX; ++i) {
        previousKeys[i] = keys[i];
    }
}

bool Input::isKeyPressed(int key) const { return keys[key]; }
bool Input::isMousePressed(int button) { return mouseButtons[button]; }
bool Input::isKeyJustPressed(int keycode) const {
    return keys[keycode] && !previousKeys[keycode];
}