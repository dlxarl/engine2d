// Builds with: pkg-config --cflags --libs allegro-5 allegro_main-5 allegro_primitives-5

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cstdio>

int main(int argc, char** argv) {
	if (!al_init()) {
		std::fprintf(stderr, "Failed to initialize Allegro\n");
		return 1;
	}

	if (!al_init_primitives_addon()) {
		std::fprintf(stderr, "Failed to initialize primitives addon\n");
		return 1;
	}

	const int width = 640;
	const int height = 480;

	ALLEGRO_DISPLAY* display = al_create_display(width, height);
	if (!display) {
		std::fprintf(stderr, "Failed to create display\n");
		return 1;
	}

	al_clear_to_color(al_map_rgb(30, 30, 60));
	al_draw_filled_rectangle(100, 100, 540, 380, al_map_rgb(200, 50, 50));
	al_flip_display();

	al_rest(2.0);

	al_destroy_display(display);
	return 0;
}
