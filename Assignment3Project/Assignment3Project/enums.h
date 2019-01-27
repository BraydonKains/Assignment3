#pragma once

#define SCREEN_W 640
#define SCREEN_H 480
#define SCREEN_R_B 560
#define SCREEN_L_B 80
#define TILE_SIZE 40
#define LEVEL_LEN 120

enum State {
	Start,
	Gameplay,
	Win,
	Lose,
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

enum BgLayer {
	Front,
	Middle,
	Back
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

struct InputDelay {
	bool input_hit;
	int delay_sec;
	int max_delay;
};