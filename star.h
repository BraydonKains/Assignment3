#pragma once
#include "game_element.h"
#include <allegro5/allegro_primitives.h>
#include "enums.h"

//Background elements, used to salvage parallax scrolling attempts
class Star : public GameElement {
public:
	BgLayer layer;

	Star();

	//Implement inhereted virtuals
	void reset_pos(float x, float y);
	void move(Direction dir);
	void draw();
	Hitbox get_hitbox();

	//Unique to element
	void set_layer(BgLayer _layer);
};