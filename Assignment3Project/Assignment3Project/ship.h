#pragma once
#include <allegro5/allegro.h>

#include "enums.h"
#include "game_element.h"
#include "bullet.h"

class Ship : public GameElement {
public:
	ALLEGRO_BITMAP* sprite;

	Ship();

	void reset_pos(float x, float y);
	void set_sprite(ALLEGRO_BITMAP* _sprite);
	void draw();
	void move(Direction dir);
	Bullet fire();
};