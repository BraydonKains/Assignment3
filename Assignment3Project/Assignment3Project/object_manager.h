#pragma once
#include <vector>

#include "enums.h"
#include "bullet.h"
#include "ship.h"
#include "star.h"

//Manages all onscreen object movements, drawing, and hitbox detection
class ObjectManager {
public:
	Ship player;
	std::vector<Ship> enemies;
	std::vector<Bullet> player_bullets;
	std::vector<Bullet> enemy_bullets; //saved for future use
	std::vector<Star> background;

	ObjectManager();

	void init_player(Ship _player);
	//Collision detection methods
	bool chk_player_col();
	int chk_bullet_col();
	//Draw objects to screen
	void draw_objects();
	//Originally for garbage collection, once moved away fromp pointers it became kind of useless
	void destroy_objects();
	//Moves all enemies on screen and checks bounds
	void move_enemies();
	//Set and move the background, originally supposed to be tilemaps now Star objects
	void set_background();
	void move_background();

private:
	//Check if two hitboxes are colliding
	bool col_eval(Hitbox h1, Hitbox h2);
};