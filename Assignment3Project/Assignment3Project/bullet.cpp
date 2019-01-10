#include "bullet.h"

Bullet::Bullet() {
	speed = 1.0;
	height = 20;
	width = 5;
}

void Bullet::reset_pos(float x, float y) {
	x_pos = x;
	y_pos = y;
}

void Bullet::draw() {
	al_draw_filled_rectangle(x_pos, y_pos, x_pos + width, y_pos + height, al_map_rgb(0,0,0));
}

void Bullet::move(Direction dir) {
}
