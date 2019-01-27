#pragma once
#include <allegro5/allegro.h>

#include "enums.h"

class GameElement {
public:
	float x_pos;
	float y_pos;
	float h_t_bound;
	float h_b_bound;
	float l_bound;
	float r_bound;
	float speed;
	float height;
	float width;
	bool oob;
	Behavior behavior;

	virtual void reset_pos(float x, float y) = 0;
	virtual void move(Direction dir) = 0;
	virtual void draw() = 0;
	virtual Hitbox get_hitbox() = 0;
};