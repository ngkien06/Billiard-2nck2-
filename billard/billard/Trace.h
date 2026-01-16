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
	bool debug_mode = true;

public:
	Trace(Color c);

public:
	void set_thickness(float th);
	void add_point(Vector2 pt);
	void clear();

	void draw();
};

#endif // !TRACER_H
