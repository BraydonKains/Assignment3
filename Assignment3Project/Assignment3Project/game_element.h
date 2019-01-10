#pragma once

#include "enums.h"

class GameElement {
public:
	float x_pos;
	float y_pos;
	float speed;
	int height;
	int width;

	virtual void reset_pos(float x, float y) = 0;
	virtual void move() = 0;
	virtual void draw(Direction dir) = 0;
};