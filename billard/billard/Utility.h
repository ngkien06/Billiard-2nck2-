#ifndef UTILITY_H
#define UTILITY_H

#include "raylib.h"

// simply for ease of use -----------------------------------------

// add 2 points/vectors
Vector2 Vector2Add(Vector2 v1, Vector2 v2);

// multifly a float to a vector
Vector2 Vector2Mul(Vector2 v, float f);

// normalize the length to 1f
Vector2 Vector2Normalize(Vector2 v);

// calculate the distancde between 2 points/vectors
float distance(Vector2 v1, Vector2 v2);

/// <summary>
/// <paramref name="p1"/>: outer right angle 
/// <paramref name="p2"/>: inner rail connect
/// <paramref name="p3"/>: inner pocket connect
/// </summary>
struct Triangle {
	Vector2 p1, p2, p3;
};

#endif // !UTILITY_H
