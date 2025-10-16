#include "Renderer.h"

void Renderer::begin() {
    al_clear_to_color(al_map_rgb(30, 30, 30));
}

void Renderer::end() {
    al_flip_display();
}
