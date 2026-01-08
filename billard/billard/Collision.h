#ifndef COLLISION_H
#define COLLISION_H

#include "Ball.h"

struct Rail;

/*
should be using Visitor patter
but to do so, I would need to have base class Entity
so for now pattern matching it is
*/ 

class CollisionHandler { 
public:
	void handle_collision(struct Rail rail, Ball& ball); // struct to make sure the complier understand it a struct
};

#endif // !COLLISION_H
