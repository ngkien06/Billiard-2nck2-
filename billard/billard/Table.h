#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include "raylib.h"

#include "Ball.h"
#include "Collision.h"

struct Rail {
	float thickness;
	Rectangle top, bottom, left1, left2 , right1, right2;

	void draw();
};

struct Pocket {
	std::pair<float, float> openings; // first: corner | second: side
	Vector2 pos[6]; // 0: top left | 1: top right | 2: middle left | 3: middle right | 4: bottom left | 5: bottom right

	void draw();
};

class Table {
private:
	Rectangle rec = { 0, 0, 150, 300 };

	Vector2 baulk;
	Vector2 apex;

	Rail rail;
	//Pocket pocket;

	std::vector<Ball> balls;
	// cue ball
	CueBall cue_ball;

	CollisionHandler collision_handler;

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
