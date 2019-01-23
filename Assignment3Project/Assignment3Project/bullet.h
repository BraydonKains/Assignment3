#pragma once
#include <allegro5/allegro_primitives.h>

#include "game_element.h"

class Bullet : public GameElement {
public:
	Bullet(Behavior _behavior);

	void reset_pos(float x, float y);
	void draw();
	void move(Direction dir);
};