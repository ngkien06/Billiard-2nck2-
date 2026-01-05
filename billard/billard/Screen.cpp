#include <string>
#include "raylib.h"

#include "Screen.h"
#include "Config.h"
#include "GUI.h"


// --------------- <Screen> ------------------------
Screen::Screen(GUI& gui) : gui_ref(gui) {}

GUI& Screen::get_gui_ref() {
	return gui_ref;
}

// --------------- <MenuScreen> ------------------------

MenuScreen::MenuScreen(GUI& gui) : Screen(gui) {
	button_play.rec = { 0, 5 * ScreenS::ScreenHeight / 8, ScreenS::ScreenWidth / 8, ScreenS::ScreenHeight / 18 };
	button_play.rec.x = ScreenS::ScreenWidth / 2 - button_play.rec.width / 2;
	button_play.txt = "Play";
	button_play.font_sz = 28;
	button_play.is_shown = true;
}

void MenuScreen::draw() {
	ClearBackground(ScreenC::C[4]);

	std::string txt = "BILLARD";
	float w = MeasureText(txt.c_str(), 48);
	DrawText(txt.c_str(), ScreenS::ScreenWidth / 2 - w / 2, ScreenS::ScreenHeight / 8, 48, ScreenC::C[0]);

	button_play.draw();
}

void MenuScreen::update() {
	handle_input();
}

void MenuScreen::handle_input() {
	if (button_play.is_clicked()) {
		GUI& gui_ref = get_gui_ref();
		std::unique_ptr<Screen> n_scr = std::make_unique<GameScreen>(gui_ref);
		gui_ref.switch_screen(std::move(n_scr));
	}
}

// --------------- <GameScreen> ------------------------

GameScreen::GameScreen(GUI& gui) : Screen(gui) {
	populate_button();
}

void GameScreen::populate_button() {
	button_back.rec = { 60 * ScreenS::ScreenWidth / 70, 65 * ScreenS::ScreenHeight / 70, ScreenS::ScreenWidth / 10, ScreenS::ScreenHeight / 22 };
	button_back.txt = "Back";
	button_back.font_sz = 20;
	button_back.is_shown = true;
}

void GameScreen::draw() {
	ClearBackground(ScreenC::C[4]);

	button_back.draw();

	// Draw divider at 6:4
	DrawLineEx({ 6 * ScreenS::ScreenWidth / 10, 0 }, { 6 * ScreenS::ScreenWidth / 10, ScreenS::ScreenHeight }, 4, ScreenC::C[3]);

	table.draw();
}

void GameScreen::update() {
	handle_input();
}

void GameScreen::handle_input() {
	if (button_back.is_clicked()) {
		GUI& gui_ref = get_gui_ref();
		std::unique_ptr<Screen> n_scr = std::make_unique<MenuScreen>(gui_ref);
		gui_ref.switch_screen(std::move(n_scr));
		return;
	}
}