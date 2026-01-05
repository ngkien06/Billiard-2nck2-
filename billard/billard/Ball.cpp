#include <stdio.h>

#include "Config.h"
#include "Ball.h"

//-------------

Vector2 Vector2Add(Vector2 v1, Vector2 v2) {
	return { v1.x + v2.x, v1.y + v2.y };
}

//-------------

Ball::Ball(int id, Vector2 pos, Color c) : index(id), position(pos), color(c) {
	this->velocity = { 0.0, 0.0 };
}

void Ball::draw() {
	float radius = 63 * ScreenS::ScreenHeight / 6400;
	DrawCircleV(position, radius, color);
	// printf("ball size: %f\n", radius * 2);
}

void Ball::update() {

}