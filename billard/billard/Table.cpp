#include "Config.h"
#include "Table.h"

Table::Table() {
	rec.width = 3.5 * ScreenS::ScreenWidth / 8;
	rec.height = 7.0 * ScreenS::ScreenWidth / 8;
	rec.x = 3 * ScreenS::ScreenWidth / 10 - rec.width / 2;
	rec.y = 1 * ScreenS::ScreenHeight / 2 - rec.height / 2;
	// 50 x 100 inches

	Vector2 offset = { rec.x, rec.y };
	baulk = Vector2Add(offset, { 0.0, 4 * rec.height / 5 });
	apex = Vector2Add(offset, { rec.width / 2, rec.height / 4 });

	//  rail 
	rail.thickness = 21 * ScreenS::ScreenHeight / 800;
	rail.top = { offset.x, offset.y - rail.thickness, rec.width, rail.thickness };
	rail.bottom = { offset.x, offset.y + rec.height, rec.width, rail.thickness };
	rail.left = { offset.x - rail.thickness, offset.y, rail.thickness, rec.height };
	rail.right = { offset.x + rec.width, offset.y, rail.thickness, rec.height };

	rack();
	cue_ball = CueBall(Vector2Add(apex, { 0.0, 3 * rec.height / 5 }));
}

void Table::rack() {
	float radius = Ball::get_radius();

	std::vector<Vector2> preset;
	preset.push_back(apex);
	preset.push_back(Vector2Add(apex, { -radius, -sqrtf(3) * radius }));
	preset.push_back(Vector2Add(apex, { +radius, -sqrtf(3) * radius }));
	preset.push_back(Vector2Add(apex, { -radius * 2, -sqrtf(3) * radius * 2 }));
	preset.push_back(Vector2Add(apex, { 0.0, -sqrtf(3) * radius * 2 }));
	preset.push_back(Vector2Add(apex, { +radius * 2, -sqrtf(3) * radius * 2 }));
	preset.push_back(Vector2Add(apex, { -radius * 3, -sqrtf(3) * radius * 3 }));
	preset.push_back(Vector2Add(apex, { -radius, -sqrtf(3) * radius * 3 }));
	preset.push_back(Vector2Add(apex, { +radius, -sqrtf(3) * radius * 3 }));
	preset.push_back(Vector2Add(apex, { +radius * 3, -sqrtf(3) * radius * 3 }));
	preset.push_back(Vector2Add(apex, { -radius * 4, -sqrtf(3) * radius * 4 }));
	preset.push_back(Vector2Add(apex, { -radius * 2, -sqrtf(3) * radius * 4 }));
	preset.push_back(Vector2Add(apex, { 0.0, -sqrtf(3) * radius * 4 }));
	preset.push_back(Vector2Add(apex, { +radius * 2, -sqrtf(3) * radius * 4 }));
	preset.push_back(Vector2Add(apex, { +radius * 4, -sqrtf(3) * radius * 4 }));

	for (int i = 0; i < preset.size(); i++) {
		Ball b = Ball(i + 1, preset[i], RED);
		balls.push_back(b);
	}
}

void Table::Rail::draw() {
	DrawRectangleRec(top, ScreenC::C[2]);
	DrawRectangleRec(bottom, ScreenC::C[2]);
	DrawRectangleRec(left, ScreenC::C[2]);
	DrawRectangleRec(right, ScreenC::C[2]);
}


// ------------------------------------

void Table::draw() {
	DrawRectangleRec(rec, ScreenC::C[1]);
	DrawLineEx(baulk, Vector2Add(baulk, { rec.width, 0.0 }), 2, WHITE); // baulk line
	DrawCircleV(apex, 3.0, ScreenC::C[2]); // apex / foot point

	rail.draw();

	for (auto b : balls) { b.draw(); }
	cue_ball.draw();
}

void Table::update() {
	for (auto b : balls) { b.update(); }
	cue_ball.update();
}

void Table::handle_input() {
	cue_ball.handle_input();
}