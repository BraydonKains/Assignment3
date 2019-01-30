#pragma once
#include <allegro5/allegro_primitives.h>

#include "game_element.h"

//Bullet fired by ships
class Bullet : public GameElement {
public:
	Bullet(Behavior _behavior);

	//implementing virtual
	void reset_pos(float x, float y);
	void draw();
	void move(Direction dir);
	Hitbox get_hitbox();
};