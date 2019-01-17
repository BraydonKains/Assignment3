#pragma once

#include "game_element.h"

class Enemy : public GameElement {
public:
	ALLEGRO_BITMAP* sprite;

	Enemy();

	void reset_pos(float x, float y);
	void draw();
	void move(Direction dir);
	void collide(GameElement* x);
};