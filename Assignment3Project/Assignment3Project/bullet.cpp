#include "bullet.h"

Bullet::Bullet(Behavior _behavior) {
	behavior = _behavior;
	switch (behavior) {
	case Enemy:
		speed = 1.0;
		height = 20;
		width = 5;
		break;
	default:
		speed = 1.0;
		height = 20;
		width = 5;
		break;
	}

	oob = false;
}

void Bullet::reset_pos(float x, float y) {
	x_pos = x;
	y_pos = y;
}

void Bullet::draw() {
	if (!oob) {
		al_draw_filled_rectangle(x_pos, y_pos, x_pos + width, y_pos + height, al_map_rgb(255, 255, 255));
	}
}

void Bullet::move(Direction dir) {
	switch (dir) {
	case U:
		y_pos -= 6;
		break;
	case D: 
		y_pos += 6;
		break;
	}
	if (y_pos < 0 - height) {
		oob = true;
	}
}

Hitbox Bullet::get_hitbox()
{
	Hitbox hitbox;
	hitbox.x = x_pos;
	hitbox.y = y_pos;
	hitbox.width = width;
	hitbox.height = height;
	return hitbox;
}
