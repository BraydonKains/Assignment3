#pragma once

#include "enums.h"
#include "game_element.h"
#include "bullet.h"

class Ship : public GameElement {
public:
	ALLEGRO_BITMAP* sprite;

	bool fired;
	
	Ship(Behavior _behavior);

	void reset_pos(float x, float y);
	void set_sprite(ALLEGRO_BITMAP* _sprite);
	void draw();
	void move(Direction dir);
	Bullet fire();
};