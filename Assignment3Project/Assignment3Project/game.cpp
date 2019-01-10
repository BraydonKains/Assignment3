#include "game.h"
#include "start_screen.h"
#include "game_screen.h"

using std::string;
using std::map;
using std::pair;

Game::Game() {
}

//Load all global data for the game: sprites, audio, and font.
void Game::init() {
	score = 0;
	state = Start;
	//sprites.insert(pair<string, ALLEGRO_BITMAP*>("Title", al_load_bitmap("logo.bmp")));


	//al_reserve_samples(4);
	//samples.insert(pair<string, ALLEGRO_SAMPLE*>("Theme", al_load_sample("rasputin.wav")));


	font = al_create_builtin_font();
}

//Was not used in this project
void Game::reset() {
}

//Run the game state machine
void Game::run() {
	//Load screens


	//Garbage collection
	map<string, ALLEGRO_BITMAP*>::iterator it;
	for (it = sprites.begin(); it != sprites.end(); it++) {
		al_destroy_bitmap(it->second);
	}
	map<string, ALLEGRO_SAMPLE*>::iterator it2;
	for (it2 = samples.begin(); it2 != samples.end(); it2++) {
		al_destroy_sample(it2->second);
	}
}