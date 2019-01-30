#include "star.h"

Star::Star() {
	oob = false;
}

void Star::reset_pos(float x, float y) {
	x_pos = x;
	y_pos = y;
}

void Star::set_layer(BgLayer _layer) {
	layer = _layer;
	//Set properties based on layer
	//Scrolls at a different speed based on layer
	switch (layer) {
	case Front:
		speed = 1.2;
		height = 1;
		width = 1;
		break;
	case Middle:
		speed = 1.0;
		height = 2;
		width = 2;
		break;
	case Back:
		speed = 0.4;
		height = 4;
		width = 4;
		break;
	}

	h_t_bound = 0 - height;
	h_b_bound = SCREEN_H + height;
	l_bound = 0;
	r_bound = SCREEN_W;
}

void Star::move(Direction dir) {
	y_pos += 4 * speed;
	if (y_pos > h_b_bound) oob = true;
}

void Star::draw() {
	al_draw_filled_rectangle(x_pos, y_pos, (x_pos + width), (y_pos + height), al_map_rgb(255, 255, 255));
}

Hitbox Star::get_hitbox() {
	return Hitbox();
}


