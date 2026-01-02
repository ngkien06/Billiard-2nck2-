#ifndef SCREEN_H
#define SCREEN_H

#include <memory>
#include <vector>

#include "Button.h"

class GUI;

class Screen {
private:
	GUI& gui_ref;

public:
	Screen(GUI& gui);

public:
	GUI& get_gui_ref();

	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void handle_input() = 0;

	virtual ~Screen() {}
};	

class MenuScreen : public Screen {
private:
	Button button_play;

public:
	MenuScreen(GUI& gui);

public:
	void draw() override;
	void update() override;
	void handle_input() override;
};

class GameScreen : public Screen {
private:
	Button button_back;

private:
	void populate_button();

public:
	GameScreen(GUI& gui);

public:
	void draw() override;
	void update() override;
	void handle_input() override;
};

#endif // !SCREEN_H

