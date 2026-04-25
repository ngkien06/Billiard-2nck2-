#include <stdio.h>
#include <math.h>
#include <algorithm>

#include "Utility.h"

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