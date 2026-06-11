#ifndef UTILITY_H
#define UTILITY_H

#include "raylib.h"

// simply for ease of use -----------------------------------------

/// <summary>
/// <paramref name="p1"/>: outer right angle 
/// <paramref name="p2"/>: inner rail connect
/// <paramref name="p3"/>: inner pocket connect
/// </summary>
struct Triangle {
	Vector2 p1, p2, p3;
};

// add 2 points/vectors
Vector2 Vector2Add(Vector2 v1, Vector2 v2);

// multifly a float to a vector
Vector2 Vector2Mul(Vector2 v, float f);

// normalize the length to 1f
Vector2 Vector2Normalize(Vector2 v);

// calculate the distancde between 2 points/vectors
float DistancePointToPoint(Vector2 v1, Vector2 v2);

// calculate the distance from a point v to a line define from 2 points p1 & p2
float DistancePointToLine(Vector2 p1, Vector2 p2, Vector2 v);

// check collision between a Circle and a Triangle
bool CheckCollisionCircleTriangle(Vector2 ct, float r, Triangle trg);

#endif // !UTILITY_H
