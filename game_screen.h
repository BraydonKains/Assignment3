#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>

#include "screen.h"
#include "ship.h"
#include "bullet.h"
#include "object_manager.h"

//Main screen for gameplay
class GameScreen : public Screen {
public:
	std::map<std::string, ALLEGRO_BITMAP*> sprites;
	std::map<std::string, ALLEGRO_SAMPLE*> samples;

	int score;
	int level;
	bool music;
	bool win;

	int map_y;

	ObjectManager objects;
	unsigned int max_bullets;
	std::vector<NewEnemy> enemy_q;

	GameScreen(std::map<std::string, ALLEGRO_BITMAP*> _sprites, std::map<std::string, ALLEGRO_SAMPLE*> _samples);

	void reset();
	void run(ALLEGRO_FONT* font);
	void redraw(ALLEGRO_FONT* font);
	void back();
	void cont();
private:
	void play(ALLEGRO_SAMPLE_INSTANCE* x);
	void build_enemy_queue();
};