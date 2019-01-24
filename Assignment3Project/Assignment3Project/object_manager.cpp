#include "object_manager.h"

using std::vector;


ObjectManager::ObjectManager() {

}

void ObjectManager::initiate(Ship * _player) {
	player = _player;
}

bool ObjectManager::chk_player_col() {
	for (vector<Ship*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
		if (col_eval(player->hitbox, (*it)->hitbox)) {
			return true;
		}
	}
}

int ObjectManager::chk_bullet_col() {
	int points = 0;
	int i = 0;
	vector<int> dead;
	for (vector<Ship*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
		for (vector<Bullet*>::iterator it_b = player_bullets.begin(); it_b != player_bullets.end(); it++) {
			if (col_eval((*it_b)->hitbox, (*it)->hitbox)) {
				switch ((*it)->behavior) {
				default:
					points += 10;
				}
				delete *it;
				dead.push_back(i);
			}
		}
		i++;
	}
	//Removed backwards to avoid indexing errors
	for (vector<int>::iterator it = dead.end(); it != dead.begin(); it--) {
		enemies.erase(enemies.begin() + *it);
	}
	return points;
}

void ObjectManager::draw_objects()
{
	player->draw();

	int i = 0;
	vector<int> dead;
	for (vector<Ship*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
		if (!(*it)->oob) {
			(*it)->draw();
		}
		else {
			dead.push_back(i);
		}
		i++;
	}
	//Removed backwards to avoid indexing errors
	for (vector<int>::iterator it = dead.end(); it != dead.begin(); it--) {
		enemies.erase(enemies.begin() + *it);
	}

	bool unload = false;
	for (unsigned int i = 0; i < player_bullets.size(); i++) {
		if (player_bullets.at(i)->oob) {
			unload = true;
		}
		else {
			player_bullets.at(i)->move(U);
			player_bullets.at(i)->draw();
		}
	}
	if (unload) {
		player_bullets.pop_back();
	}
}

void ObjectManager::destroy_objects() {
	delete player;

	for (vector<Ship*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
		delete *it;
	}
	enemies.clear();

	for (vector<Bullet*>::iterator it = player_bullets.begin(); it != player_bullets.end(); it++) {
		delete *it;
	}
	player_bullets.clear();

	for (vector<Bullet*>::iterator it = enemy_bullets.begin(); it != enemy_bullets.end(); it++) {
		delete *it;
	}
	enemy_bullets.clear();
}

void ObjectManager::move_enemies() {
	for (vector<Ship*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
		(*it)->move(D);
	}
}

bool ObjectManager::col_eval(Hitbox h1, Hitbox h2) {
	if ((h1.x > h2.x && h1.x < (h2.x + h2.width)) && (h1.y > h2.y && h1.y < (h2.y + h2.height))) {
		return true;
	}
}