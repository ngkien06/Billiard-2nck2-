#include "Collision.h"
#include "Table.h"

void CollisionHandler::handle_collision(Rail rail, Ball& ball) {
	Vector2 b_pos = ball.get_pos();
	float r = Ball::get_radius();

	if (CheckCollisionCircleRec(b_pos, r, rail.bottom)) {
		Vector2 normal = { 0.0, -1.0 };
		float penetration_depth = b_pos.y - (rail.bottom.y) + r;
		ball.displace_position(normal, penetration_depth);

		ball.bounce_horizontal();
	}
	if (CheckCollisionCircleRec(b_pos, r, rail.top)) {
		Vector2 normal = { 0.0, 1.0 };
		float penetration_depth = (rail.top.y + rail.thickness) - b_pos.y + r;
		ball.displace_position(normal, penetration_depth);

		ball.bounce_horizontal();
	}
	if (CheckCollisionCircleRec(b_pos, r, rail.left)) {
		Vector2 normal = { 1.0, 0.0 };
		float penetration_depth = (rail.left.x + rail.thickness) - b_pos.x + r;
		ball.displace_position(normal, penetration_depth);
		
		ball.bounce_vertical();
	}
	if (CheckCollisionCircleRec(b_pos, r, rail.right)) {
		Vector2 normal = { -1.0, 0.0 };
		float penetration_depth = b_pos.x - (rail.right.x) + r;
		ball.displace_position(normal, penetration_depth);
		
		ball.bounce_vertical();
	}
}