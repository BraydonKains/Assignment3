#pragma once

#define SCREEN_W 640
#define SCREEN_H 480
#define SCREEN_R_B 600
#define SCREEN_L_B 40
#define TILE_SIZE 40
#define LEVEL_LEN 120

enum State {
	Start,
	Gameplay,
	End,
	Exit
};

enum Direction {
	U,
	D,
	L,
	R,
	UR,
	UL,
	DR,
	DL
};

enum Behavior {
	Player,
	Enemy
};

struct Hitbox {
	int x;
	int y;
	int height;
	int width;
};

struct NewEnemy {
	int x;
	Behavior e_type;
	int when;
};