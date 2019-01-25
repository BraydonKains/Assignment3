#include "object_manager.h"

using std::vector;


ObjectManager::ObjectManager() {

}

void ObjectManager::initiate(Ship * _player) {
	player = _player;
}

bool ObjectManager::chk_player_col() {
	if (enemies.size() > 0) {
		for (vector<Ship*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
			if (col_eval(player->get_hitbox(), (*it)->get_hitbox())) {
				return true;
			}
		}
	}
	return false;
}

int ObjectManager::chk_bullet_col() {
	int points = 0;
	if (enemies.size() > 0 && player_bullets.size() > 0) {
		int i = 0;
		vector<int> dead;
		for (vector<Ship*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
			for (vector<Bullet*>::iterator it_b = player_bullets.begin(); it_b != player_bullets.end(); it_b++) {
				if (col_eval((*it_b)->get_hitbox(), (*it)->get_hitbox())) {
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
			delete enemies.at(*it);
			enemies.erase(enemies.begin() + *it);
		}
	}
	return points;
}

void ObjectManager::draw_objects()
{
	player->draw();

	if (enemies.size() > 0) {
		int i = 0;
		vector<int> oob_ships;
		for (vector<Ship*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
			if (!(*it)->oob) {
				(*it)->draw();
			}
			else {
				oob_ships.push_back(i);
			}
			i++;
		}
		//Removed backwards to avoid indexing errors
		for (vector<int>::iterator it = oob_ships.end(); it != oob_ships.begin(); it--) {
			enemies.erase(enemies.begin() + *it);
		}
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

	if (enemies.size() > 0) {
		for (vector<Ship*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
			delete *it;
		}
		enemies.clear();
	}

	if (player_bullets.size() > 0) {
		for (vector<Bullet*>::iterator it = player_bullets.begin(); it != player_bullets.end(); it++) {
			delete *it;
		}
		player_bullets.clear();
	}

	if (enemy_bullets.size() > 0) {
		for (vector<Bullet*>::iterator it = enemy_bullets.begin(); it != enemy_bullets.end(); it++) {
			delete *it;
		}
		enemy_bullets.clear();
	}
}

void ObjectManager::move_enemies() {
	if (enemies.size() > 0) {
		for (vector<Ship*>::iterator it = enemies.begin(); it != enemies.end(); it++) {
			(*it)->move(D);
		}
	}
}

bool ObjectManager::col_eval(Hitbox h1, Hitbox h2) {
	int l1x = h1.x;
	int l1y = h1.y;
	int r1x = h1.x + h1.width;
	int r1y = h1.y + h1.height;

	int l2x = h2.x;
	int l2y = h2.y;
	int r2x = h2.x + h2.width;
	int r2y = h2.y + h2.height;

	/*if (h1.x > (h2.x + h2.width) || h2.x > (h1.x + h1.width))
		return false;

	if (h1.y < (h2.y + h2.height) || h2.y < (h1.y + h1.height))
		return false;*/

		// If one rectangle is on left side of other 
	if (l1x > r2x || l2x > r1x)
		return false;

	// If one rectangle is above other 
	if (l1y < r2y || l2y < r1y)
		return false;

	return true;
}