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

private:
	void rack();

public:
	Table();

public:
	void draw();
	void update();
};

#endif // !TABLE_H
