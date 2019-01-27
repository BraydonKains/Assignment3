#include "ship.h"

Ship::Ship() {
}

void Ship::reset_pos(float x, float y) {
	x_pos = x;
	y_pos = y;
}

void Ship::set_props(ALLEGRO_BITMAP* _sprite, Behavior _behavior) {
	sprite = _sprite;
	behavior = _behavior;
	oob = false;
	switch (behavior) {
	case Enemy:
		speed = 1.1;
		height = 40;
		width = 40;

		l_bound = SCREEN_L_B;
		r_bound = SCREEN_R_B;
		h_t_bound = 0 - height;
		h_b_bound = SCREEN_H + height;
		break;
	default:
		speed = 1.0;
		height = 40;
		width = 40;

		l_bound = SCREEN_L_B;
		r_bound = SCREEN_R_B;
		r_bound -= width;
		h_t_bound = 0;
		h_b_bound = SCREEN_H - height;
		break;
	}
}

void Ship::draw() {
	al_draw_bitmap(sprite, x_pos, y_pos, (behavior == Player) ? NULL : ALLEGRO_FLIP_VERTICAL);
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
		if (behavior == Player) {
			x_pos = l_bound;
		}
		else oob = true;
	}
	else if (x_pos >= r_bound) {
		if (behavior == Player) {
			x_pos = r_bound;
		}
		else oob = true;
	}
	if (y_pos <= h_t_bound) {
		if (behavior == Player) {
			y_pos = h_t_bound;
		}
		else oob = true;
	}
	else if (y_pos >= h_b_bound) {
		if (behavior == Player) {
			y_pos = h_b_bound;
		}
		else oob = true;
	}
}

Hitbox Ship::get_hitbox()
{
	Hitbox hitbox;
	hitbox.x = x_pos;
	hitbox.y = y_pos;
	hitbox.width = width;
	hitbox.height = height;
	return hitbox;
}

Bullet Ship::fire() {
	Bullet new_bullet(behavior);
	float x = (x_pos) + width / 2.0;
	float y = y_pos - new_bullet.height;
	new_bullet.reset_pos(x, y);
	fired = true;
	return new_bullet;
}