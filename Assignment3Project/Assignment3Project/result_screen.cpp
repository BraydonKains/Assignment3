#include <vector>
#include <sstream>
#include "result_screen.h"

using std::string;
using std::vector;
using std::ostringstream;

ResultScreen::ResultScreen() {
	vector<string> menu_options;
	menu_options.push_back("Retry"); //Restart game
	menu_options.push_back("To Main Menu"); //Go back to main menu
	menu_options.push_back("Exit"); //Quit game
	menu.activate(menu_options);
}

void ResultScreen::run(ALLEGRO_FONT* font) {
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	redraw(font);
	al_flip_display();

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
				//Select menu item
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
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_destroy_event_queue(event_queue);
}

void ResultScreen::redraw(ALLEGRO_FONT * font) {
	//Determine whether the player receives the bad or good ending; minimum requirement for good ending is 30 catches.
	string result_text = (win) ? "You made it literally all the way across space! Wow!" : "Oh no, you died!";

	//Display score and menu
	menu.draw(SCREEN_W / 2 - 40, SCREEN_H / 2 - 30, 20.0, font);
	ostringstream score_msg;
	score_msg << "Final Score: " << score;
	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2 - 90, ALLEGRO_ALIGN_CENTER, score_msg.str().c_str());

	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_W / 2, SCREEN_H / 2 - 60, ALLEGRO_ALIGN_CENTER, result_text.c_str());
}

void ResultScreen::back() {
	next_state = Exit;
}

void ResultScreen::cont() {
	string result = menu.get_selected();
	if (result == "Retry") {
		next_state = Gameplay;
	}
	else if (result == "To Main Menu") {
		next_state = Start;
	}
	else {
		next_state = Exit;
	}
}
