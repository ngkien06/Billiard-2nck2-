#ifndef TRACER_H
#define TRACER_H

#include <vector>

#include "raylib.h"

class Trace {
private:
	std::vector<Vector2> points;
	Color color;
	float thickness = 7.f;

	int limit = 50; // only record n points max
	bool is_dissipate = false;
	float accum_time = 0.0;

	bool debug_mode = false;

public:
	Trace(Color c);

public:
	void set_thickness(float th);
	void add_point(Vector2 pt);
	void dissipate();
	void clear();

	void draw();
	void update();
};

#endif // !TRACER_H
