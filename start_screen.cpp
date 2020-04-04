#include "start_screen.h"

#include <vector>
#include <string>

using std::vector;
using std::string;

StartScreen::StartScreen(std::map<std::string, ALLEGRO_BITMAP*> _sprites) {
	vector<string> menu_options;
	menu_options.push_back("Start"); //Start game
	menu_options.push_back("Quit"); //Quit game
	menu.activate(menu_options);

	sprites = _sprites;
}

void StartScreen::reset() {
	
}

//Run screen
void StartScreen::run(ALLEGRO_FONT * font) {
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	redraw(font);
	menu.draw(300.0, 400.0, 20.0, font);
	al_flip_display();

	bool ctrl = false;
	bool exit_screen = false;
	while (!exit_screen) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_W:
			case ALLEGRO_KEY_UP:
				//Move cursor up
				menu.up();
				break;
			case ALLEGRO_KEY_S:
			case ALLEGRO_KEY_DOWN:
				//Move cursor down
				menu.down();
				break;
			case ALLEGRO_KEY_SPACE:
				//Select item
				cont();
				exit_screen = true;
				break;
			case ALLEGRO_KEY_ESCAPE:
				//Force quit game
				back();
				exit_screen = true;
				break;
			}
			redraw(font);
			al_flip_display();
		}
	}

	//Garbage collection
	al_destroy_event_queue(event_queue);
}

void StartScreen::redraw(ALLEGRO_FONT* font) {
	//Logo
	al_draw_bitmap(sprites["Title"], SCREEN_W / 2 - 240, 20, NULL); 
	
	//Instructions
	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 3, ALLEGRO_ALIGN_CENTER, "Journey to the end of space");
	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 3 + 10, ALLEGRO_ALIGN_CENTER, "and kill the red ships!");
	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 3 + 20, ALLEGRO_ALIGN_CENTER, "Red is a bad colour that must be eradicated.");

	//Keys and their associated functions
	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 12, SCREEN_H / 1.5 - 10, ALLEGRO_ALIGN_LEFT, "WASD or Arrows - Move ship");

	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 12, SCREEN_H / 1.3 - 20, ALLEGRO_ALIGN_LEFT, "Spacebar - Shoot, select menu item");

	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 12, SCREEN_H / 2 + 150, ALLEGRO_ALIGN_LEFT, "Esc - Exit Game");

	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2 + 113, SCREEN_H / 1.5 - 10, ALLEGRO_ALIGN_LEFT, "Ctrl + H - Open help menu");

	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2 + 113, SCREEN_H / 1.3 - 20, ALLEGRO_ALIGN_LEFT, "Ctrl + M - Toggle Music");
	
	al_draw_text(font, al_map_rgb(255, 255, 255), 0, SCREEN_H - 10, ALLEGRO_ALIGN_LEFT, "Copyright 2019 Braydon Kains");
}

void StartScreen::back() {
	next_state = Exit;
}

void StartScreen::cont() {
	if (menu.get_selected() == "Start") {
		next_state = Gameplay;
	}
	else {
		next_state = Exit;
	}
}