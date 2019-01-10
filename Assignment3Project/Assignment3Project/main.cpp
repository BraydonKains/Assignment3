#include <stdio.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>

#include "game.h"

int main() {
	if (!al_init()) {
		fprintf(stderr, "Could not initialize Allegro!");
	}
	if (!al_init_image_addon()) {
		fprintf(stderr, "Could not initialize image addon!");
	}
	if (!al_init_acodec_addon()) {
		fprintf(stderr, "Could not initialize audio codec addon!");
	}
	if (!al_install_audio()) {
		fprintf(stderr, "Could not install audio!");
	}
	if (!al_init_font_addon()) {
		fprintf(stderr, "Could not initialize font addon!");
	}
	if (!al_install_keyboard()) {
		fprintf(stderr, "Could not install keyboard!");
	}
	if (!al_init_primitives_addon()) {
		fprintf(stderr, "Could not initialize primitives addon!");
	}

	ALLEGRO_DISPLAY* display = NULL;
	display = al_create_display(SCREEN_W, SCREEN_H);

	Game main_game;
	main_game.init();
	main_game.run();

	al_uninstall_keyboard();
	al_uninstall_audio();

	return 0;
}