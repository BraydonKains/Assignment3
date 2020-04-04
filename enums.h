#pragma once

#define SCREEN_W 640
#define SCREEN_H 480
#define SCREEN_R_B 560
#define SCREEN_L_B 80
#define TILE_SIZE 40
#define LEVEL_LEN 120

//State machine states
enum State {
	Start,
	Gameplay,
	Win,
	Lose,
	Exit
};

//Movement directions
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

//Game object behaviors
enum Behavior {
	Player,
	Enemy
};

//Define current background layer for scrolling
enum BgLayer {
	Front,
	Middle,
	Back
};

//Game object hitbox for collision detection
struct Hitbox {
	int x;
	int y;
	int height;
	int width;
};

//Struct for enemy queue
struct NewEnemy {
	int x;
	Behavior e_type;
	int when;
};

//When inputs must be delayed by a number of frames (no longer used, kept for possible future use
struct InputDelay {
	bool input_hit;
	int delay_sec;
	int max_delay;
};