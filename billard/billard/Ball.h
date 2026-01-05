#ifndef BALL_H
#define BALL_H

#include "raylib.h"

class Ball {
private:
	int index;

	Vector2 position; // in the whole screen
	Vector2 velocity;

	Color color;

public:
	Ball(int id, Vector2 pos, Color c);

public:
	void draw();
	void update();
};

// simply for ease of use
Vector2 Vector2Add(Vector2 v1, Vector2 v2);

#endif // !BALL_H
