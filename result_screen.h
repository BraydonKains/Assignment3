#pragma once
#include "cursor.h"
#include "screen.h"

//Screen to display results upon losing
class ResultScreen : public Screen {
public:
	int score;
	Cursor<std::string> menu;
	std::map<std::string, ALLEGRO_BITMAP*> sprites;
	bool win;

	ResultScreen();

	void run(ALLEGRO_FONT* font);
	void redraw(ALLEGRO_FONT* font);
	void back();
	void cont();
};