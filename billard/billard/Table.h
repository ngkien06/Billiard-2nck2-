#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include "raylib.h"

#include "Ball.h"

class Table {
private:
	Rectangle rec = { 0, 0, 150, 300 };

	Vector2 baulk;
	Vector2 apex;

	struct Rail {
		float thickness;
		Rectangle top, bottom, left, right;

		void draw();
	} rail;

	std::vector<Ball> balls;
	// cue ball
	CueBall cue_ball;

private:
	void rack();

public:
	Table();

public:
	void handle_input();
	void update();
	void draw();
};

#endif // !TABLE_H
