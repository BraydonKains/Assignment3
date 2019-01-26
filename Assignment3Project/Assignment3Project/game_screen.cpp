#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <ctime>

//#include "mappy_A5.h"

#include "game_screen.h"

#define FPS 60

using std::vector;
using std::string;
using std::ostringstream;
using std::istringstream;
using std::ifstream;
using std::map;
using std::pair;

enum KEYS {
	KEYUP, KEYDOWN, KEYLEFT, KEYRIGHT, KEYSPACE, KEYCTRL, KEYH, KEYM, KEYESC
};

GameScreen::GameScreen(std::map<std::string, ALLEGRO_BITMAP*> _sprites, std::map<std::string, ALLEGRO_SAMPLE*> _samples) {
	sprites = _sprites;
	samples = _samples;
	srand(time(NULL)); //Seed random number generator with current time so sequence is unique each run
}

//Resets game to default values, and uses new given values
void GameScreen::reset() {
	objects.player = new Ship(Player);
	objects.player->set_sprite(sprites["Ship"]);
	objects.player->reset_pos(SCREEN_W / 2, SCREEN_H / 8);
	max_bullets = 3;
}

//If a sample needs to be played while it is still being played, it will be stopped first.
//Admittedly this was a hack solution to the fact that my sound effect samples are too long. 
//In future projects I will use a better program for sound effect creation that does not have a large minimum length for audio export.
void GameScreen::play(ALLEGRO_SAMPLE_INSTANCE* x) {
	if (al_get_sample_instance_playing(x)) {
		al_stop_sample_instance(x);
	}
	al_play_sample_instance(x);
}

void GameScreen::build_enemy_queue() {
	string line;
	ifstream enemies_file("enemies.txt");

	if (enemies_file.is_open()) {
		while (getline(enemies_file, line)) {
			NewEnemy next;
			istringstream curr_line(line);
			string element;
			//Get enemy type (when there's other types of enemies I'll fix this)
			getline(curr_line, element, ',');
			next.e_type = Enemy; 
			//Get appearance time
			getline(curr_line, element, ',');
			next.when = stoi(element);
			//Get position
			getline(curr_line, element, ',');
			next.x = stoi(element);
			enemy_q.push_back(next);
		}
	}

	enemies_file.close();
}

void GameScreen::run(ALLEGRO_FONT* font) {
	ALLEGRO_EVENT_QUEUE* event_queue = NULL;
	event_queue = al_create_event_queue();
	al_register_event_source(event_queue, al_get_keyboard_event_source());

	ALLEGRO_TIMER* timer = NULL;
	timer = al_create_timer(1.0 / FPS);
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	build_enemy_queue();
	bool more_enemies = true;
	NewEnemy next_enemy = enemy_q.back();
	enemy_q.pop_back();

	map<string, InputDelay> inputs;
	inputs.insert(pair<string, InputDelay>("Fire", InputDelay()));
	inputs.insert(pair<string, InputDelay>("Music", InputDelay()));
	inputs.insert(pair<string, InputDelay>("Help", InputDelay()));
	

	map_y = TILE_SIZE * LEVEL_LEN;

	redraw(font);
	al_flip_display();
	
	bool keys[ALLEGRO_KEY_MAX];
	for (int i = 0; i < ALLEGRO_KEY_MAX; i++) keys[i] = false;

	al_start_timer(timer);
	bool exit_screen = false;
	while (!exit_screen) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER) { //Check per frame
			//Music toggle
			if (keys[KEYCTRL] && keys[KEYM]) {
				music = !music;
			}

			//Ship Movement
			if (keys[KEYUP]) {
				if (keys[KEYRIGHT]) {
					objects.player->move(UR);
				}
				else if (keys[KEYLEFT]) {
					objects.player->move(UL);
				}
				else {
					objects.player->move(U);
				}
			}
			else if (keys[KEYDOWN]) {
				if (keys[KEYRIGHT]) {
					objects.player->move(DR);
				}
				else if (keys[KEYLEFT]) {
					objects.player->move(DL);
				}
				else {
					objects.player->move(D);
				}
			}
			else if (keys[KEYLEFT]) {
				objects.player->move(L);
			}
			else if (keys[KEYRIGHT]) {
				objects.player->move(R);
			}

			//Firing
			if (keys[KEYSPACE]) {
				if (objects.player_bullets.size() < max_bullets) {
					if (!objects.player->fired) {
						objects.player_bullets.push_back(&objects.player->fire());
					}
					objects.player->fired = true;
				}
			}
			if (objects.player->fired) {
				if (fired_counter >= 20) {
					objects.player->fired = false;
					fired_counter = 0;
				}
				else {
					fired_counter++;
				}
			}

			if (map_y > 0) {
				map_y -= 10;
			}
			else {
				exit_screen = true;
			}

			if (more_enemies && map_y >= next_enemy.when) {
				Ship* new_e = new Ship(next_enemy.e_type);
				new_e->set_sprite(sprites["Enemy"]);
				new_e->reset_pos(next_enemy.x, 0 - new_e->height + 1);
				objects.enemies.push_back(new_e);
				if (enemy_q.size() > 0) {
					next_enemy = enemy_q.back();
					enemy_q.pop_back();
				}
				else {
					more_enemies = false;
				}
			}
						
			//Global refresh
			if (objects.chk_player_col()) {
				exit_screen = true;
			}
			//score += objects.chk_bullet_col();
			objects.move_enemies();
			al_clear_to_color(al_map_rgb(0, 0, 0));
			redraw(font);
			al_flip_display();
		}
		if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_S:
			case ALLEGRO_KEY_DOWN:
				keys[KEYDOWN] = true;
				break;
			case ALLEGRO_KEY_W:
			case ALLEGRO_KEY_UP:
				keys[KEYUP] = true;
				break;
			case ALLEGRO_KEY_D:
			case ALLEGRO_KEY_RIGHT:
				keys[KEYRIGHT] = true;
				break;
			case ALLEGRO_KEY_A:
			case ALLEGRO_KEY_LEFT:
				keys[KEYLEFT] = true;
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
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_UP) {
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_S:
			case ALLEGRO_KEY_DOWN:
				keys[KEYDOWN] = false;
				break;
			case ALLEGRO_KEY_W:
			case ALLEGRO_KEY_UP:
				keys[KEYUP] = false;
				break;
			case ALLEGRO_KEY_D:
			case ALLEGRO_KEY_RIGHT:
				keys[KEYRIGHT] = false;
				break;
			case ALLEGRO_KEY_A:
			case ALLEGRO_KEY_LEFT:
				keys[KEYLEFT] = false;
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
		}
	}
	if (next_state != Exit) { //If the game loop was exited naturally rather than forced by Esc
		cont();
	}

	//Garbage collection
	//MapFreeMem();
	objects.destroy_objects();
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
}

//Redraw all elements of the screen
void GameScreen::redraw(ALLEGRO_FONT* font) {
	//MapDrawBG(0, map_y, 0, SCREEN_L_B, SCREEN_W - 80, SCREEN_H);
 
	objects.draw_objects();

	ostringstream score_msg;
	score_msg << "Score: " << score;
	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_R_B + 2, 0, ALLEGRO_ALIGN_LEFT, score_msg.str().c_str());

	string music_img = (music) ? "MusicOn" : "MusicOff";
	al_draw_bitmap(sprites[music_img], SCREEN_R_B + 10, 90, NULL);
}

void GameScreen::back() {
	next_state = Exit;
}

void GameScreen::cont() {
	next_state = Start;
}