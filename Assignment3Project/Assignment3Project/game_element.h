#pragma once
#include <allegro5/allegro.h>

#include "enums.h"

class GameElement {
public:
	float x_pos;
	float y_pos;
	float speed;
	float height;
	float width;
	bool oob;

	virtual void reset_pos(float x, float y) = 0;
	virtual void move(Direction dir) = 0;
	virtual void draw() = 0;
};