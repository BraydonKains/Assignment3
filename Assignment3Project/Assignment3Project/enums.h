#pragma once

#define SCREEN_W 640
#define SCREEN_H 480

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