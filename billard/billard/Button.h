#ifndef BUTTON_H
#define BUTTON_H

#include <string>
#include "raylib.h" 

struct Button {
	Rectangle rec = { 0.0, 0.0 };
	std::string txt;
	int font_sz = 0.0;
	bool is_shown = true;

	void draw();
	bool is_hovered();
	bool is_clicked();
};

#endif // !BUTTON_H