#include "object_manager.h"

using std::vector;

ObjectManager::ObjectManager() {

}

void ObjectManager::initiate(Ship * _player) {
	player = _player;
}

bool ObjectManager::chk_player_col() {
	return false;
}

int ObjectManager::chk_bullet_col() {
	return 0;
}

void ObjectManager::draw_objects()
{
	player->draw();

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

