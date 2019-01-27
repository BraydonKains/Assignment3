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
#include "help_screen.h"

#define FPS 60

using std::vector;
using std::string;
using std::ostringstream;
using std::istringstream;
using std::ifstream;
using std::map;
using std::pair;
using std::rand;

enum KEYS {
	KEYUP, KEYDOWN, KEYLEFT, KEYRIGHT, KEYSPACE, KEYCTRL, KEYH, KEYM, KEYESC
};

enum ACTIONS {
	FIRE, MUSIC, HELP
};

GameScreen::GameScreen(std::map<std::string, ALLEGRO_BITMAP*> _sprites, std::map<std::string, ALLEGRO_SAMPLE*> _samples) {
	sprites = _sprites;
	samples = _samples;
	srand(time(NULL)); //Seed random number generator with current time so sequence is unique each run
}

//Resets game to default values, and uses new given values
void GameScreen::reset() {
	music = true;
	win = false;
	score = 0;

	Ship player;
	player.set_props(sprites["Ship"], Player);
	player.reset_pos(SCREEN_W / 2, SCREEN_H / 1.2);
	objects.init_player(player);
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

	InputDelay inputs[3];
	inputs[FIRE].input_hit = false;
	inputs[FIRE].delay_sec = 0;
	inputs[FIRE].max_delay = 15;

	inputs[MUSIC].input_hit = false;
	inputs[MUSIC].delay_sec = 0;
	inputs[MUSIC].max_delay = 80;

	inputs[HELP].input_hit = false;
	inputs[HELP].delay_sec = 0;
	inputs[HELP].max_delay = 80;

	int max_map = TILE_SIZE * LEVEL_LEN;
	map_y = max_map;
	objects.set_background();

	redraw(font);
	al_flip_display();
	
	bool keys[ALLEGRO_KEY_MAX];
	for (int i = 0; i < ALLEGRO_KEY_MAX; i++) keys[i] = false;

	map<string, ALLEGRO_SAMPLE_INSTANCE*> instances;
	map<string, ALLEGRO_SAMPLE*>::iterator it;
	for (it = samples.begin(); it != samples.end(); it++) {
		instances.insert(pair<string, ALLEGRO_SAMPLE_INSTANCE*>(it->first, al_create_sample_instance(it->second)));
		al_attach_sample_instance_to_mixer(instances[it->first], al_get_default_mixer());
	}
	al_set_sample_instance_playmode(instances["Theme"], ALLEGRO_PLAYMODE_LOOP);
	float music_vol = 0.5;
	al_set_sample_instance_gain(instances["Theme"], music_vol);
	play(instances["Theme"]);
	al_set_sample_instance_gain(instances["Hit"], 2.2);

	al_start_timer(timer);
	bool exit_screen = false;
	while (!exit_screen) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);
		if (ev.type == ALLEGRO_EVENT_TIMER) { //Check per frame
			//Music toggle
			if (!inputs[MUSIC].input_hit) {
				if (keys[KEYCTRL] && keys[KEYM]) {
					if (music) {
						al_set_sample_instance_gain(instances["Theme"], 0.0);
					}
					else {
						al_set_sample_instance_gain(instances["Theme"], music_vol);
					}
					music = !music;
					inputs[MUSIC].input_hit = true;
				}
			}

			//Ship Movement
			if (keys[KEYUP]) {
				if (keys[KEYRIGHT]) {
					objects.player.move(UR);
				}
				else if (keys[KEYLEFT]) {
					objects.player.move(UL);
				}
				else {
					objects.player.move(U);
				}
			}
			else if (keys[KEYDOWN]) {
				if (keys[KEYRIGHT]) {
					objects.player.move(DR);
				}
				else if (keys[KEYLEFT]) {
					objects.player.move(DL);
				}
				else {
					objects.player.move(D);
				}
			}
			else if (keys[KEYLEFT]) {
				objects.player.move(L);
			}
			else if (keys[KEYRIGHT]) {
				objects.player.move(R);
			}

			//Firing
			if (!inputs[FIRE].input_hit) {
				if (keys[KEYSPACE] && objects.player_bullets.size() < max_bullets) {
					objects.player_bullets.push_back(objects.player.fire());
					inputs[FIRE].input_hit = true;
					play(instances["Fire"]);
				}
			}

			//Help menu
			if (!inputs[HELP].input_hit) {
				if (keys[KEYCTRL] && keys[KEYH]) {
					HelpScreen help_screen;
					al_clear_to_color(al_map_rgb(0, 0, 0));
					help_screen.run(font);
					al_clear_to_color(al_map_rgb(0, 0, 0));
					keys[KEYCTRL] = false;
					keys[KEYH] = false;
				}
			}

			//Move map (HAHAHA THE MAP DIDN'T WORK AND I GAVE UP this is just a glorified timer now)
			if (map_y > 0) {
				map_y -= 2;
			}
			else if(objects.enemies.size() == 0) {
				win = true;
				exit_screen = true;
				al_stop_sample_instance(instances["Theme"]);
				al_set_sample_instance_gain(instances["Win"], music_vol);
				al_play_sample_instance(instances["Win"]);
			}

			/* This may be used in the next assignment, this functionality is for scripting enemy appearance
			//Check if the next enemy is due
			if (more_enemies && (max_map - map_y) >= next_enemy.when) {
				//If he is, generate the new ship for the enemy and set the next enemy up
				Ship new_e;
				new_e.set_props(sprites["Enemy"], next_enemy.e_type);
				new_e.reset_pos(next_enemy.x + SCREEN_L_B, 0 - new_e.height + 1);
				objects.enemies.push_back(new_e);
				//Only queue up a new enemy if there is one, if there isn't then set the flag for no more enemies
				if (enemy_q.size() > 0) {
					next_enemy = enemy_q.back();
					enemy_q.pop_back();
				}
				else {
					more_enemies = false;
				}
			}*/

			//Random enemy generation
			if (map_y > 20) { //Should only generate if not right near the end
				int enemy_chance = rand() % 80; //1 in 20 chance to generate an enemy
				if (enemy_chance == 4) {
					Ship new_e;
					new_e.set_props(sprites["Enemy"], Enemy);
					new_e.reset_pos(rand() % ((SCREEN_R_B - (int)new_e.width) - SCREEN_L_B + 1) + SCREEN_L_B, 0 - new_e.height + 1);
					objects.enemies.push_back(new_e);
				}
			}

			if (keys[KEYESC]) {
				exit_screen = true;
				next_state = Exit;
			}
						
			//Global refresh
			if (objects.chk_player_col()) {
				exit_screen = true;
				al_stop_sample_instance(instances["Theme"]);
				play(instances["Die"]);
			}
			int points = objects.chk_bullet_col();
			if (points > 0) {
				score += points;
				play(instances["Hit"]);
			}
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
				inputs[FIRE].input_hit = false;
				break;
			case ALLEGRO_KEY_M:
				keys[KEYM] = false;
				inputs[MUSIC].input_hit = false;
				break;
			case ALLEGRO_KEY_H:
				keys[KEYH] = false;
				inputs[HELP].input_hit = false;
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

	al_clear_to_color(al_map_rgb(0, 0, 0));
	//Garbage collection
	objects.destroy_objects();
	al_destroy_event_queue(event_queue);
	al_destroy_timer(timer);
}

//Redraw all elements of the screen
void GameScreen::redraw(ALLEGRO_FONT* font) {
	//MapDrawBG(0, map_y, 0, SCREEN_L_B, SCREEN_W - 80, SCREEN_H);
 
	objects.draw_objects();

	//Borders
	al_draw_filled_rectangle(SCREEN_L_B - 1, 0, SCREEN_L_B, SCREEN_H, al_map_rgb(255,255,255));
	al_draw_filled_rectangle(SCREEN_R_B, 0, SCREEN_R_B + 1, SCREEN_H, al_map_rgb(255,255,255));

	//Score
	ostringstream score_msg;
	score_msg << "" << score;
	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_R_B + 2, 0, ALLEGRO_ALIGN_LEFT, "Score: ");
	al_draw_text(font, al_map_rgb(255, 255, 255), SCREEN_R_B + 2, 10, ALLEGRO_ALIGN_LEFT, score_msg.str().c_str());

	//Music
	string music_img = (music) ? "MusicOn" : "MusicOff";
	al_draw_bitmap(sprites[music_img], SCREEN_R_B + 10, 40, NULL);
}

void GameScreen::back() {
	next_state = Exit;
}

void GameScreen::cont() {
	next_state = (win) ? Win : Lose;
}