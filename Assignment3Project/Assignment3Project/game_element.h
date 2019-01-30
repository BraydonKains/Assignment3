#pragma once
#include <allegro5/allegro.h>

#include "enums.h"

//Game Element base class, with position, height, and screen bounding properties along with its behavior
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
	
	//Set position of object
	virtual void reset_pos(float x, float y) = 0;
	//Move object
	virtual void move(Direction dir) = 0;
	//Draw object to screen
	virtual void draw() = 0;
	//Build hitbox struct for the object at position in current frame
	virtual Hitbox get_hitbox() = 0;
};