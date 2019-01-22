#pragma once

#include "enums.h"
#include "game_element.h"
#include "bullet.h"

class Ship : public GameElement {
public:
	ALLEGRO_BITMAP* sprite;

	bool fired;
	float h_bound;
	float l_bound;
	float r_bound;

	Ship();

	void reset_pos(float x, float y);
	void set_sprite(ALLEGRO_BITMAP* _sprite);
	void draw();
	void move(Direction dir);
	Bullet fire();
};