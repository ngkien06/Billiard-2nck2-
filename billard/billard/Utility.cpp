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

float DistancePointToPoint(Vector2 v1, Vector2 v2) {
	return sqrtf((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
}

float DistancePointToLine(Vector2 p1, Vector2 p2, Vector2 v) {
	Vector2 ab = { p2.x - p1.x, p2.y - p1.y };
	Vector2 av = { v.x - p1.x, v.y - p1.y };

	float t = (av.x * ab.x + av.y * ab.y) / (ab.x * ab.x + ab.y * ab.y);
	t = fmaxf(0.0f, fminf(1.0f, t)); // clamp to [0,1] — keeps point on segment

	Vector2 closest = { p1.x + t * ab.x, p1.y + t * ab.y };

	float dx = v.x - closest.x;
	float dy = v.y - closest.y;
	return sqrtf(dx * dx + dy * dy);
}

bool CheckCollisionCircleTriangle(Vector2 ct, float r, Triangle trg) {
	if (CheckCollisionPointTriangle(ct, trg.p1, trg.p2, trg.p3)) { return true; }

	if (DistancePointToLine(trg.p2, trg.p3, ct) <= r) { 
		printf("distance from (%f, %f) to (%f,%f) - (%f,%f): %f \n", ct.x, ct.y, trg.p2.x, trg.p2.y, trg.p3.x, trg.p3.y, DistancePointToLine(trg.p2, trg.p3, ct));
		return true;
	} // here only care about te outer edge?

	return false;
}