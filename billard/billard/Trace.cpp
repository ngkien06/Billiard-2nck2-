#include "Trace.h"

Trace::Trace(Color c) {
	color = { c.r, c.g, c.b, (unsigned char)(c.a * 0.6) };
}

void Trace::set_thickness(float th) {
	this->thickness = th;
}

void Trace::add_point(Vector2 pt) {
	points.push_back(pt);
}

void Trace::dissipate() {
	float delta_time = GetFrameTime();
	accum_time += delta_time;

	if (accum_time >= 0.2) { 
		points.erase(points.begin()); 
	}

	if (points.empty() == false) { is_dissipate = true; }
	else { is_dissipate = false; }
}

void Trace::clear() {
	points.clear();
}

void Trace::draw() {
	for (auto pt : points) {
		DrawCircleV(pt, thickness / 2, color);
	}
}

void Trace::update() {
	if (is_dissipate == true) { dissipate(); }

	if (debug_mode == true) { return; }
	while (points.size() > limit) { points.erase(points.begin()); }
}