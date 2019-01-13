#include "ship.h"

Ship::Ship() {
	speed = 1.0;
	height = 40;
	width = 40;
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
}

Bullet Ship::fire() {
	Bullet new_bullet;
	reset_pos((x_pos + width) / 2, y_pos + new_bullet.height);
	return new_bullet;
}