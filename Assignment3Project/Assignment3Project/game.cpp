#include "game.h"

using std::string;
using std::map;
using std::pair;

Game::Game() {
}

//Load all global data for the game: sprites, audio, and font.
void Game::init() {
	score = 0;
	state = Start;
	sprites.insert(pair<string, ALLEGRO_BITMAP*>("Ship", al_load_bitmap("placeholder.bmp")));
	sprites.insert(pair<string, ALLEGRO_BITMAP*>("Enemy", al_load_bitmap("enemy.bmp")));
	sprites.insert(pair<string, ALLEGRO_BITMAP*>("MusicOn", al_load_bitmap("music_on.bmp")));
	sprites.insert(pair<string, ALLEGRO_BITMAP*>("MusicOff", al_load_bitmap("music_off.bmp")));

	al_reserve_samples(4);
	samples.insert(pair<string, ALLEGRO_SAMPLE*>("Theme", al_load_sample("cheesetheme.wav")));
	
	font = al_create_builtin_font();
}

//Was not used in this project
void Game::reset() {
}

//Run the game state machine
void Game::run() {
	//Load screens
	StartScreen start_screen(sprites);
	GameScreen game_screen(sprites, samples);

	while (state != Exit) {
		switch (state) {
		case Start:
			//start_screen.reset();
			start_screen.run(font);
			state = start_screen.next_state;
			break;
		case Gameplay:
			game_screen.reset();
			game_screen.run(font);
			state = game_screen.next_state;
			break;
		}
	}

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