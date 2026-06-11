#ifndef BALL_H
#define BALL_H

#include "raylib.h"

#include "Trace.h"

enum class ball_status { STATIONARY, MOVING, AIMING, PLACING, POCKETED };

class Ball {
protected:
	int index;

	Vector2 position; // in the whole screen
	Vector2 velocity;
	Color color;
	
	Trace trace;

	ball_status status;

	static float radius;
	void initialize_radius();

	static float drag_rolling;
	void initialize_drag();

	// cor: coefficient of restitution, is dimentionless
	static float cor_rail, cor_ball;

	// for debugging purposed
	float time_travel = 0.0;
	float distance_travel = 0.0;

	void set_velocity_vector(float v);

public:
	Ball(int id, Vector2 pos, Color c);

public:
	Vector2 get_pos();
	static float get_radius();

	virtual void draw();
	virtual void update();

	void displace_position(Vector2 vector, float distance);
	void bounce_vertical();
	void bounce_horizontal();
};

class CueBall : public Ball {
private:
	static float MAX_SPEED, MIN_SPEED;
	void initialize_speed();

	bool debug_mode = true;

public:
	CueBall();
	CueBall(Vector2 pos);

public:
	void draw() override;
	void update() override;
	void handle_input();
};

#endif // !BALL_H
