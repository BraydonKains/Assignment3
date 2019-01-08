#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <ctime>

#include "game_screen.h"

#define FPS 60

using std::vector;
using std::string;
using std::ostringstream;
using std::map;
using std::pair;

enum KEYS {
	KEYUP, KEYDOWN, KEYSPACE, KEYCTRL, KEYH, KEYM, KEYESC
};

GameScreen::GameScreen(std::map<std::string, ALLEGRO_BITMAP*> _sprites, std::map<std::string, ALLEGRO_SAMPLE*> _samples) {
	sprites = _sprites;
	samples = _samples;
	srand(time(NULL)); //Seed random number generator with current time so sequence is unique each run
}

//Resets game to default values, and uses new given values
void GameScreen::reset(int _lines, int _max_catchers, int _difficulty) {
	
}

//If a sample needs to be played while it is still being played, it will be stopped first.
//Admittedly this was a hack solution to the fact that my sound effect samples are too long. 
//In future projects I will use a better program for sound effect creation that does not have a large minimum length for audio export.
void play(ALLEGRO_SAMPLE_INSTANCE* x) {
	if (al_get_sample_instance_playing(x)) {
		al_stop_sample_instance(x);
	}
	al_play_sample_instance(x);
}

void GameScreen::run(ALLEGRO_FONT* font) {
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	ALLEGRO_TIMER* timer = NULL;
	timer = al_create_timer(1.0 / FPS); //Universally a "tick" in the context of the game is 1/10 of a second.
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	redraw(font);
	al_flip_display();

	bool keys[ALLEGRO_KEY_MAX];
	for (int i = 0; i < ALLEGRO_KEY_MAX; i++) keys[i] = false;

	al_start_timer(timer);
	bool exit_screen;
	while (!exit_screen) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER) {
			if (keys[KEYUP]) {
				//Up is pressed!
			}
		}
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_DOWN:
				keys[KEYDOWN] = true;
				break;
			case ALLEGRO_KEY_UP:
				keys[KEYUP] = true;
				break;
			case ALLEGRO_KEY_SPACE:
				keys[KEYSPACE] = true;
				break;
			case ALLEGRO_KEY_M:
				keys[KEYM] = true;
				break;
			case ALLEGRO_KEY_H:
				keys[KEYH] = true;
				break;
			case ALLEGRO_KEY_ESCAPE:
				keys[KEYESC] = true;
				break;
			case ALLEGRO_KEY_LCTRL:
			case ALLEGRO_KEY_RCTRL:
				keys[KEYCTRL] = true;
				break;
			}
			if (ev.type == ALLEGRO_EVENT_KEY_UP) {
				switch (ev.keyboard.keycode) {
				case ALLEGRO_KEY_DOWN:
					keys[KEYDOWN] = false;
					break;
				case ALLEGRO_KEY_UP:
					keys[KEYUP] = false;
					break;
				case ALLEGRO_KEY_SPACE:
					keys[KEYSPACE] = false;
					break;
				case ALLEGRO_KEY_M:
					keys[KEYM] = false;
					break;
				case ALLEGRO_KEY_H:
					keys[KEYH] = false;
					break;
				case ALLEGRO_KEY_ESCAPE:
					keys[KEYESC] = false;
					break;
				case ALLEGRO_KEY_LCTRL:
				case ALLEGRO_KEY_RCTRL:
					keys[KEYCTRL] = false;
					break;
			}
			//Global refresh
			al_clear_to_color(al_map_rgb(0, 0, 0));
			redraw(font);
			al_flip_display();
		}
	}
	if (next_state != Exit) { //If the game loop was exited naturally rather than forced by Esc
		cont();
	}

	//Garbage collection
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
}

//Redraw all elements of the screen
void GameScreen::redraw(ALLEGRO_FONT* font) {

}

void GameScreen::back() {
	next_state = Exit;
}

void GameScreen::cont() {
	next_state = End;
}