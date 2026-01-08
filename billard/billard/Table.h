#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include "raylib.h"

#include "Ball.h"
#include "Collision.h"

struct Rail {
	float thickness;
	Rectangle top, bottom, left, right;

	void draw();
};

class Table {
private:
	Rectangle rec = { 0, 0, 150, 300 };

	Vector2 baulk;
	Vector2 apex;

	Rail rail;

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
