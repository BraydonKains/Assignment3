#pragma once

#include "enums.h"
#include "game_element.h"
#include "bullet.h"

//Ship sprite displayed over background
class Ship : public GameElement {
public:
	ALLEGRO_BITMAP* sprite; //loads a sprite rather than a primitive

	bool fired; //no longer used
	
	Ship();

	//implementing virtual methods
	void reset_pos(float x, float y);
	void draw();
	void move(Direction dir);
	Hitbox get_hitbox();

	void set_props(ALLEGRO_BITMAP* _sprite, Behavior _behavior); //Sets ship properties
	Bullet fire(); //Creates a new bullet
};