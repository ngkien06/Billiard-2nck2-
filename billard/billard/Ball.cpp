#include <stdio.h>
#include <math.h>
#include <algorithm>

#include "Config.h"
#include "Ball.h"

//-------------

Vector2 Vector2Add(Vector2 v1, Vector2 v2) {
	return { v1.x + v2.x, v1.y + v2.y };
}

Vector2 Vector2Mul(Vector2 v, float f) {
	return { v.x * f, v.y * f };
}

Vector2 Vector2Normalize(Vector2 v) {
	if (v.x == 0.0 and v.y == 0.0) { return v; }
	float t = sqrtf(v.x * v.x + v.y * v.y);
	return Vector2Mul(v, 1 / t);
}

float distance(Vector2 v1, Vector2 v2) {
	return sqrtf((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

//------------- <Ball> ------------

float Ball::radius = 0.0;
float Ball::drag = 0.0;

void Ball::initialize_radius() {
	radius = 63 * ScreenS::ScreenHeight / 6400;
	printf("radius: %f\n\n", radius);
	// 2.25 inches
}

void Ball::initialize_drag() {
	drag = 1351 * ScreenS::ScreenHeight / 40000;
	// 0.098 m/s^2 or 3.86 in/s^2 
}

Ball::Ball(int id, Vector2 pos, Color c) : index(id), position(pos), color(c), status(ball_status::ACTIVE) {
	this->velocity = { 0.0, 0.0 };

	if (radius == 0.0) { initialize_radius(); }
	if (drag == 0.0) { initialize_drag(); }
}

// --------

Vector2 Ball::get_pos() {
	return position;
}

float Ball::get_radius() {
	return radius;
}

void Ball::draw() {
	DrawCircleV(position, radius, color);
}

void Ball::update() {
	float delta_time = GetFrameTime();

	// update velocity
	float new_velocity = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y);
	new_velocity = std::max(0.f, new_velocity - Ball::drag * delta_time);
	velocity = Vector2Mul(Vector2Normalize(velocity), new_velocity);
	if (new_velocity > 0.0) {
		printf("velocity: %f (%f, %f)\n", new_velocity, velocity.x, velocity.y);
		this->distance_travel += new_velocity * delta_time;
		this->time_travel += delta_time;
	}

	// update position
	position.x += velocity.x * delta_time;
	position.y += velocity.y * delta_time;
}

// --------

void Ball::displace_position(Vector2 vector, float distance) {
	this->position = Vector2Add(this->position, Vector2Mul(vector, distance));
}

void Ball::bounce_horizontal() {
	this->velocity.y = -(this->velocity.y);
}

void Ball::bounce_vertical() {
	this->velocity.x = -(this->velocity.x);
}

// ----------------------------- <CueBall> ----------------------------

float CueBall::MAX_SPEED = 0.0, CueBall::MIN_SPEED = 0.0;

void CueBall::initialize_speed() {
	MIN_SPEED = 1239 * ScreenS::ScreenHeight / 8000;
	MAX_SPEED = 861 * ScreenS::ScreenHeight / 500;
	// 0.45 m/s - 5 m/s or 17.7 in/s - 196.8 in/s
}

CueBall::CueBall() : Ball(0, { 0, 0 }, WHITE), curr_action(cue_action::STATIONARY) {
	if (MIN_SPEED == MAX_SPEED) { initialize_speed(); } // a bit nonsense, but i just need it to run once
}

CueBall::CueBall(Vector2 pos) : Ball(0, pos, WHITE), curr_action(cue_action::STATIONARY) {}

// --------

void CueBall::draw() {
	Ball::draw();

	if (curr_action == cue_action::AIMING) {
		Vector2 mouse = GetMousePosition();
		Vector2 pos = get_pos();

		if (distance(mouse, pos) <= 90.0) { // 90 is max length, if change also change in handle_input
			DrawLineEx(pos, mouse, 1.5, WHITE);
		}
		else {
			Vector2 v = Vector2Add(mouse, Vector2Mul(pos, -1.0)); // minus the long way 
			v = Vector2Normalize(v);
			v = Vector2Mul(v, 90.0);

			DrawLineEx(pos, Vector2Add(pos, v), 1.5, WHITE);
		}
	} // should this be here? or in Table::draw()



	//printf("velocity: (%f, %f)\n", velocity.x, velocity.y);
}

void CueBall::update() {
	Ball::update();

	switch (curr_action)
	{
	case cue_action::MOVING:
		if (velocity.x == 0.0 && velocity.y == 0.0) { 
			curr_action = cue_action::STATIONARY;
			printf("distance traveled: %f | time traveled: %f \n", this->distance_travel, this->time_travel);
			distance_travel = 0.0; time_travel = 0.0;
		}
		break;
	case cue_action::AIMING:
		break;
	case cue_action::PLACING:
		break;
	default:
		break;
	}
}

void CueBall::handle_input() {
	Vector2 mouse = GetMousePosition();
	Vector2 pos = get_pos();

	switch (curr_action) {
	case cue_action::STATIONARY: {
		if (CheckCollisionPointCircle(mouse, pos, get_radius()) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			curr_action = cue_action::AIMING;
		}
		break;
	}
	case cue_action::AIMING:
		if (IsKeyPressed(KEY_C)) { curr_action = cue_action::STATIONARY; }

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) == false) { 
			float d = std::min(distance(mouse, pos), 90.0f);
			float speed = MIN_SPEED + (d / 90.0f) * (MAX_SPEED - MIN_SPEED);

			Vector2 v = Vector2Add(pos, Vector2Mul(mouse, -1.0));
			v = Vector2Normalize(v);
			v = Vector2Mul(v, speed);
			this->velocity = v;

			curr_action = cue_action::MOVING; 
		} 
		break;
	case cue_action::PLACING:
		break;
	default:
		break;
	}
}