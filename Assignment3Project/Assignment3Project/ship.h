#pragma once

#include "enums.h"
#include "game_element.h"
#include "bullet.h"

class Ship : public GameElement {
public:
	ALLEGRO_BITMAP* sprite;

	bool fired;
	
	Ship();

	//implementing virtual methods
	void reset_pos(float x, float y);
	void draw();
	void move(Direction dir);
	Hitbox get_hitbox();

	//unique to object
	void set_props(ALLEGRO_BITMAP* _sprite, Behavior _behavior);
	Bullet fire();
};