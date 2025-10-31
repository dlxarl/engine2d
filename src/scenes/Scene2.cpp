#include "headers/Scene2.h"
#include "headers/Scene1.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

void Scene2::update(float dt, const Input& input) {
    timer += dt;

    // Наприклад, автоматичний перехід через 5 секунд
    if (timer > 5.0f) {
        finished = true;
    }

    // Або: перехід по клавіші
    ALLEGRO_KEYBOARD_STATE state;
    al_get_keyboard_state(&state);
    if (al_key_down(&state, ALLEGRO_KEY_ENTER)) {
        finished = true;
    }
}

void Scene2::draw(Renderer& r) {
    r.clear(Color(30, 30, 60));

    // Малюємо простий текст
    ALLEGRO_FONT* font = al_create_builtin_font();
    al_draw_text(font, al_map_rgb(255, 255, 255), 400, 300, ALLEGRO_ALIGN_CENTER, "Це сцена 2. Натисни Enter...");
    al_destroy_font(font);
}

bool Scene2::isFinished() const {
    return finished;
}

Scene* Scene2::nextScene() const {
    return new Scene1(); // або new Scene3();
}