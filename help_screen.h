#pragma once
#include "screen.h"
#include "cursor.h"
#include <string>

//Screen to display help menu
class HelpScreen : public Screen {
public:
	Cursor<std::string> menu;

	HelpScreen();

	void run(ALLEGRO_FONT* font);
	void redraw(ALLEGRO_FONT* font);
	void back();
	void cont();
};