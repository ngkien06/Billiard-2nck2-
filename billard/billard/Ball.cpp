#include <stdio.h>
#include <math.h>
#include <algorithm>

#include "Config.h"
#include "Utility.h"
#include "Ball.h"

//------------- <Ball> ------------

float Ball::radius = 0.0;
float Ball::drag_rolling = 0.0;
float Ball::cor_rail = 0.6; 
float Ball::cor_ball = 0.98;

void Ball::initialize_radius() {
	radius = 63 * ScreenS::ScreenHeight / 6400;
	printf("radius: %f\n", radius);
	// 2.25 inches
}

void Ball::initialize_drag() {
	drag_rolling = 4053 * ScreenS::ScreenHeight / 80000;
	// 0.147 m/s^2 or 5.79 in/s^2 
}

Ball::Ball(int id, Vector2 pos, Color c) : index(id), position(pos), color(c), status(ball_status::STATIONARY), trace(Trace(c)) {
	this->velocity = { 0.0, 0.0 };

	if (radius == 0.0) { initialize_radius(); }
	if (drag_rolling == 0.0) { initialize_drag(); }

	trace.set_thickness(Ball::radius);
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
	
	trace.draw();
}

void Ball::update() {
	float delta_time = GetFrameTime();

	switch (status)	{
	case ball_status::STATIONARY:
		trace.update();
		break;
	case ball_status::MOVING: {
		// update velocity
		float new_velocity = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y);
		new_velocity = std::max(0.f, new_velocity - Ball::drag_rolling * delta_time);
		set_velocity_vector(new_velocity);

		// for debugging purposes
		if (new_velocity > 0.0) {
			//printf("velocity: %f (%f, %f)\n", new_velocity, velocity.x, velocity.y);
			this->distance_travel += new_velocity * delta_time;
			this->time_travel += delta_time;
		}

		// trace
		if (new_velocity > 0) {
			trace.add_point(position);
			trace.update();
		}
		else { trace.dissipate(); }

		// update position
		position.x += velocity.x * delta_time;
		position.y += velocity.y * delta_time;

		if (velocity.x == 0.0 && velocity.y == 0.0) {
			status = ball_status::STATIONARY;
			printf("distance traveled: %f | time traveled: %f \n", this->distance_travel, this->time_travel);
			distance_travel = 0.0; time_travel = 0.0;
		}

		break;
	}
	default:
		break;
	}
}

// --------

void Ball::set_velocity_vector(float v) {
	this->velocity = Vector2Mul(Vector2Normalize(this->velocity), v);
}

void Ball::displace_position(Vector2 vector, float distance) {
	this->position = Vector2Add(this->position, Vector2Mul(vector, distance));
}

void Ball::bounce_horizontal() {
	this->velocity.y = -(this->velocity.y);
	
	float new_velocity = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y) * Ball::cor_rail;
	set_velocity_vector(new_velocity);
}

void Ball::bounce_vertical() {
	this->velocity.x = -(this->velocity.x);

	float new_velocity = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y) * Ball::cor_rail;
	set_velocity_vector(new_velocity);
}

// ----------------------------- <CueBall> ----------------------------

float CueBall::MAX_SPEED = 0.0, CueBall::MIN_SPEED = 0.0;

void CueBall::initialize_speed() {
	MIN_SPEED = 1239 * ScreenS::ScreenHeight / 8000;
	MAX_SPEED = 861 * ScreenS::ScreenHeight / 500;
	// 0.45 m/s - 5 m/s or 17.7 in/s - 196.8 in/s
}

CueBall::CueBall() : Ball(0, { 0, 0 }, WHITE) {
	if (MIN_SPEED == MAX_SPEED) { initialize_speed(); } // a bit nonsense, but i just need it to run once
}

CueBall::CueBall(Vector2 pos) : Ball(0, pos, WHITE) {}

// --------

void CueBall::draw() {
	Ball::draw();

	if (status == ball_status::AIMING) {
		Vector2 mouse = GetMousePosition();
		Vector2 pos = get_pos();

		if (DistancePointToPoint(mouse, pos) <= 90.0) { // 90 is max length, if change also change in handle_input
			DrawLineEx(pos, mouse, 1.5, WHITE);
		}
		else {
			Vector2 v = Vector2Add(mouse, Vector2Mul(pos, -1.0)); // minus the long way 
			v = Vector2Normalize(v);
			v = Vector2Mul(v, 90.0);

			DrawLineEx(pos, Vector2Add(pos, v), 1.5, WHITE);
			if (debug_mode == true) {
				Vector2 v_temp = Vector2Mul(v, -10);
				DrawLineEx(pos, Vector2Add(pos, v_temp), 1.5, WHITE);

				DrawCircleV(Vector2Add(pos, v), 3.0f, RED);
				DrawCircleV(Vector2Add(pos, v_temp), 3.0f, GREEN);
			}
		}
	} // should this be here? or in Table::draw()



	//printf("velocity: (%f, %f)\n", velocity.x, velocity.y);
}

void CueBall::update() {
	Ball::update();
}

void CueBall::handle_input() {
	Vector2 mouse = GetMousePosition();
	Vector2 pos = get_pos();

	switch (status) {
	case ball_status::STATIONARY: {
		if (CheckCollisionPointCircle(mouse, pos, get_radius()) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			status = ball_status::AIMING;
		}
		break;
	}
	case ball_status::AIMING:
		if (IsKeyPressed(KEY_C)) { status = ball_status::STATIONARY; }

		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON) == false) { 
			float d = std::min(DistancePointToPoint(mouse, pos), 90.0f);
			float speed = MIN_SPEED + (d / 90.0f) * (MAX_SPEED - MIN_SPEED);

			Vector2 v = Vector2Add(pos, Vector2Mul(mouse, -1.0));
			v = Vector2Normalize(v);
			v = Vector2Mul(v, speed);
			this->velocity = v;

			status = ball_status::MOVING;
		} 
		break;
	case ball_status::PLACING:
		break;
	default:
		break;
	}
}