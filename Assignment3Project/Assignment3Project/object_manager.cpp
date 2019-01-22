#include "object_manager.h"

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
