#include "ship.h"

Ship::Ship() {
	speed = 1.0;
	height = 40;
	width = 40;
	
	l_bound = 50;
	r_bound = 590;
	r_bound -= width;
	h_bound = SCREEN_H;
	h_bound -= height;
}

void Ship::reset_pos(float x, float y) {
	x_pos = x;
	y_pos = y;
}

void Ship::set_sprite(ALLEGRO_BITMAP* _sprite) {
	sprite = _sprite;
}

void Ship::draw() {
	al_draw_bitmap(sprite, x_pos, y_pos, NULL);
}

void Ship::collide(GameElement * x)
{
}

void Ship::move(Direction dir) {
	float factor = 4 * speed;
	switch (dir) {
	case U:
		y_pos -= factor;
		break;
	case D:
		y_pos += factor;
		break;
	case R:
		x_pos += factor;
		break;
	case L:
		x_pos -= factor;
		break;
	case UR:
		x_pos += factor; 
		y_pos -= factor;
		break;
	case UL:
		x_pos -= factor;
		y_pos -= factor;
		break;
	case DR:
		x_pos += factor;
		y_pos += factor;
		break;
	case DL:
		x_pos -= factor;
		y_pos += factor;
		break;
	}

	if (x_pos <= l_bound) {
		x_pos = l_bound;
	}
	else if (x_pos >= r_bound) {
		x_pos = r_bound;
	}
	if (y_pos <= 0.0) {
		y_pos = 0.0;
	}
	else if (y_pos >= h_bound) {
		y_pos = h_bound;
	}
}

Bullet Ship::fire() {
	Bullet new_bullet;
	float x = (x_pos) + width / 2.0;
	float y = y_pos - new_bullet.height;
	new_bullet.reset_pos(x, y);
	fired = true;
	return new_bullet;
}