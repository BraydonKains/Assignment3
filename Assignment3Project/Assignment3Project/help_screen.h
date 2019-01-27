#pragma once
#include "screen.h"
#include "cursor.h"
#include <string>

//Screen to display results upon losing
class HelpScreen : public Screen {
public:
	std::map<std::string, ALLEGRO_BITMAP*> sprites;
	Cursor<std::string> menu;

	HelpScreen();

	void run(ALLEGRO_FONT* font);
	void redraw(ALLEGRO_FONT* font);
	void back();
	void cont();
};