#include "Trace.h"

int Trace::limit = 50;

Trace::Trace(Color c) {
	color = { c.r, c.g, c.b, (unsigned char)(c.a * 0.6) };
}

void Trace::set_thickness(float th) {
	this->thickness = th;
}

void Trace::add_point(Vector2 pt) {
	points.push_back(pt);
	
	if (points.size() > limit) { points.erase(points.begin()); }
}

void Trace::clear() {
	points.clear();
}

void Trace::draw() {
	for (auto pt : points) {
		DrawCircleV(pt, thickness / 2, color);
	}
}