#include "bullet.h"

Bullet::Bullet() {
	speed = 1.0;
	height = 20;
	width = 5;
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
	y_pos -= 6;
	if (y_pos < 0 - height) {
		oob = true;
	}
}