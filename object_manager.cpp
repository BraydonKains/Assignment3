#include "object_manager.h"
#include <ctime>

using std::vector;
using std::rand;

ObjectManager::ObjectManager() {
	srand(time(NULL));
}

void ObjectManager::init_player(Ship _player) {
	player = _player;
}

bool ObjectManager::chk_player_col() {
	if (enemies.size() > 0) {
		for (vector<Ship>::iterator it = enemies.begin(); it != enemies.end(); it++) {
			if (col_eval(player.get_hitbox(), (*it).get_hitbox())) {
				return true;
			}
		}
	}
	return false;
}

int ObjectManager::chk_bullet_col() {
	int points = 0;
	if (enemies.size() > 0 && player_bullets.size() > 0) {
		int d = 0;
		vector<int> dead;
		vector<int> kill_bullets;
		for (vector<Ship>::iterator it = enemies.begin(); it != enemies.end(); it++) {
			int b = 0;
			for (vector<Bullet>::iterator it_b = player_bullets.begin(); it_b != player_bullets.end(); it_b++) {
				if (col_eval((*it_b).get_hitbox(), (*it).get_hitbox())) {
					switch ((*it).behavior) {
					default:
						points += 10;
					}
					dead.push_back(d);
					kill_bullets.push_back(b);
				}
				b++;
			}
			d++;
		}
		//Removed backwards to avoid indexing errors
		for (unsigned int x = dead.size(); x > 0; x--) {
			enemies.erase(enemies.begin() + dead.at(x - 1));
		}
		for (unsigned int x = kill_bullets.size(); x > 0; x--) {
			player_bullets.erase(player_bullets.begin() + kill_bullets.at(x - 1));
		}
	}
	return points;
}

void ObjectManager::draw_objects()
{
	vector<int> unload;
	move_background();
	for (unsigned int k = 0; k < background.size(); k++) {
		if (background.at(k).oob) {
			unload.push_back(k);
		}
		else {
			background.at(k).draw();
		}
	}
	for (unsigned int j = unload.size(); j > 0; j--) {
		background.erase(background.begin() + unload.at(j - 1));
	}

	player.draw();

	if (enemies.size() > 0) {
		int i = 0;
		vector<int> oob_ships;
		for (unsigned int k = 0; k < enemies.size(); k++) {
			if (!enemies.at(k).oob) {
				enemies.at(k).draw();
			}
			else {
				oob_ships.push_back(i);
			}
			i++;
		}
		//Removed backwards to avoid indexing errors
		for (unsigned int x = oob_ships.size(); x > 0; x--) {
			enemies.erase(enemies.begin() + oob_ships.at(x - 1));
		}
	}

	unload.clear();
	for (unsigned int k = 0; k < player_bullets.size(); k++) {
		if (player_bullets.at(k).oob) {
			unload.push_back(k);
		}
		else {
			player_bullets.at(k).move(U);
			player_bullets.at(k).draw();
		}
	}
	for (unsigned int j = unload.size(); j > 0; j--) {
		player_bullets.erase(player_bullets.begin() + unload.at(j - 1));
	} 
}

void ObjectManager::destroy_objects() {
	enemies.clear();
	player_bullets.clear();
	enemy_bullets.clear();
}

void ObjectManager::move_enemies() {
	if (enemies.size() > 0) {
		for (vector<Ship>::iterator it = enemies.begin(); it != enemies.end(); it++) {
			(*it).move(D);
		}
	}
}

//Initialize background stars
void ObjectManager::set_background() {
	for (int i = 0; i < 20; i++) {
		//Pick random layer and position
		Star new_star; 
		int l = rand() % 2;
		BgLayer layer;
		switch (l) {
		case 0:
			layer = Front;
			break;
		case 1:
			layer = Middle;
			break;
		case 2:
			layer = Back;
			break;
		}
		int y = rand() % SCREEN_H;
		int x = rand() % (SCREEN_R_B - SCREEN_L_B + 1) + SCREEN_L_B;
		new_star.reset_pos(x, y);
		new_star.set_layer(layer);
		background.push_back(new_star);
	}
}

void ObjectManager::move_background() {
	for (unsigned int i = 0; i < background.size(); i++) {
		background.at(i).move(D);
	}
	int generate_chance = rand() % 2;
	if (generate_chance) {
		Star new_star;
		int l = rand() % 2;
		BgLayer layer;
		switch (l) {
		case 0:
			layer = Front;
			break;
		case 1:
			layer = Middle;
			break;
		case 2:
			layer = Back;
			break;
		}
		int x = rand() % (SCREEN_R_B - SCREEN_L_B + 1) + SCREEN_L_B;
		new_star.set_layer(layer);
		new_star.reset_pos(x, new_star.h_t_bound);
		background.push_back(new_star);
	}
}

//Check if the hitboxes are overlapping
bool ObjectManager::col_eval(Hitbox h1, Hitbox h2) {
	//Check if one hitbox is within the other's width
	if (h1.x > (h2.x + h2.width) || h2.x > (h1.x + h1.width))
		return false;

	//Check if one hitbox is within the other's height
	if (h1.y > (h2.y + h2.height) || h2.y > (h1.y + h1.height))
		return false;

	return true;
}