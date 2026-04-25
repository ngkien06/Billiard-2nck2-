#include "Config.h"
#include "Utility.h"
#include "Table.h"

// -------------------------- <Rail> --------------------------

void Rail::draw() {
	DrawRectangleRec(top, ScreenC::C[2]);
	DrawRectangleRec(bottom, ScreenC::C[2]);
	DrawRectangleRec(left1, ScreenC::C[2]);
	DrawRectangleRec(left2, ScreenC::C[2]);
	DrawRectangleRec(right1, ScreenC::C[2]);
	DrawRectangleRec(right2, ScreenC::C[2]);

	for (int i = 0; i < 12; i++) {
		DrawTriangle(triangles[i].p1, triangles[i].p2, triangles[i].p3, ScreenC::C[2]);

		/*
		DrawCircleV(triangles[i].p1, 3.0f, RED);
		DrawCircleV(triangles[i].p2, 3.0f, GREEN);
		DrawCircleV(triangles[i].p3, 3.0f, YELLOW);
		*/
	}

	/*
	Vector2 debug_p1 = { top.x, top.y + top.height };
	Vector2 debug_p2 = { left1.x + left1.width, left1.y };
	DrawCircleV(debug_p1, 3.0f, RED);
	DrawCircleV(debug_p2, 3.0f, RED);
	//printf("corner space: %f\n", distance(debug_p1, debug_p2));
	*/
}

// -------------------------- <Pocket> --------------------------

void Pocket::draw() {
	
}

// -------------------------- <Table> --------------------------

Table::Table() {
	rec.width = 3.5 * ScreenS::ScreenWidth / 8;
	rec.height = 7.0 * ScreenS::ScreenWidth / 8;
	rec.x = 3 * ScreenS::ScreenWidth / 10 - rec.width / 2;
	rec.y = 1 * ScreenS::ScreenHeight / 2 - rec.height / 2;
	// 50 x 100 inches
	printf("table at (%f, %f) to (%f, %f)\n", rec.x, rec.y, rec.x + rec.width, rec.y + rec.height);

	Vector2 offset = { rec.x, rec.y };
	baulk = Vector2Add(offset, { 0.0, 4 * rec.height / 5 });
	apex = Vector2Add(offset, { rec.width / 2, rec.height / 4 });

	float pk_space1 = (63 / sqrtf(8)) * ScreenS::ScreenWidth / 800; // space for corner pocket
	float pk_space2 = (35 / 2.0) * ScreenS::ScreenWidth / 800; // space for side pocket

	//  rail 
	rail.thickness = 17.5 * ScreenS::ScreenHeight / 800; // 2.5 inches
	rail.top = { offset.x + pk_space1, offset.y - rail.thickness, rec.width - (2 * pk_space1), rail.thickness };
	rail.bottom = { offset.x + pk_space1, offset.y + rec.height, rec.width - (2 * pk_space1), rail.thickness};
	rail.left1 = { offset.x - rail.thickness, offset.y + pk_space1, rail.thickness, rec.height / 2 - (pk_space1 + pk_space2) };
	rail.left2 = { offset.x - rail.thickness, offset.y + rec.height / 2 + pk_space2, rail.thickness, rec.height / 2 - (pk_space1 + pk_space2) };
	rail.right1 = { offset.x + rec.width, offset.y + pk_space1, rail.thickness, rec.height / 2 - (pk_space1 + pk_space2) };
	rail.right2 = { offset.x + rec.width, offset.y + rec.height / 2 + pk_space2,  rail.thickness, rec.height / 2 - (pk_space1 + pk_space2) };
	printf("rail thickness: %f\n", rail.thickness);
	
	// triangle rail
	rail.triangles[0]  = { {rail.left1.x, rail.left1.y}, {rail.left1.x + rail.thickness, rail.left1.y}, {rail.left1.x, rail.left1.y - rail.thickness} };
	rail.triangles[1]  = { {rail.top.x, rail.top.y}, {rail.top.x - rail.thickness, rail.top.y}, {rail.top.x, rail.top.y + rail.thickness} };
	rail.triangles[2]  = { {rail.top.x + rail.top.width, rail.top.y}, {rail.top.x + rail.top.width, rail.top.y + rail.thickness}, {rail.top.x + rail.top.width + rail.thickness, rail.top.y} };
	rail.triangles[3]  = { {rail.right1.x + rail.right1.width, rail.right1.y}, {rail.right1.x + rail.right1.width, rail.right1.y - rail.thickness}, {rail.right1.x, rail.right1.y} };
	rail.triangles[4]  = { {rail.right1.x + rail.right1.width, rail.right1.y + rail.right1.height}, {rail.right1.x, rail.right1.y + rail.right1.height}, {rail.right1.x + rail.right1.width, rail.right1.y + rail.right1.height + (rail.thickness / 2.25f)} };
	rail.triangles[5]  = { {rail.right2.x + rail.right2.width, rail.right2.y}, {rail.right2.x + rail.right2.width, rail.right2.y - (rail.thickness / 2.25f)}, {rail.right2.x, rail.right2.y} };
	rail.triangles[6]  = { {rail.right2.x + rail.right2.width, rail.right2.y + rail.right2.height}, {rail.right2.x, rail.right2.y + rail.right2.height}, {rail.right2.x + rail.right2.width, rail.right2.y + rail.right2.height + rail.thickness} };
	rail.triangles[7]  = { {rail.bottom.x + rail.bottom.width, rail.bottom.y + rail.bottom.height}, {rail.bottom.x + rail.bottom.width + rail.thickness, rail.bottom.y + rail.bottom.height}, {rail.bottom.x + rail.bottom.width, rail.bottom.y} };
	rail.triangles[8]  = { {rail.bottom.x, rail.bottom.y + rail.bottom.height}, {rail.bottom.x, rail.bottom.y}, {rail.bottom.x - rail.thickness, rail.bottom.y + rail.bottom.height} };
	rail.triangles[9]  = { {rail.left2.x, rail.left2.y + rail.left2.height}, {rail.left2.x, rail.left2.y + rail.left2.height + rail.thickness}, {rail.left2.x + rail.left2.width, rail.left2.y + rail.left2.height} };
	rail.triangles[10] = { {rail.left2.x, rail.left2.y}, {rail.left2.x + rail.left2.width, rail.left2.y}, {rail.left2.x, rail.left2.y - (rail.thickness / 2.25f)} };
	rail.triangles[11] = { {rail.left1.x, rail.left1.y + rail.left1.height}, {rail.left1.x, rail.left1.y + rail.left1.height + (rail.thickness / 2.25f)}, {rail.left1.x + rail.left1.width, rail.left1.y + rail.left1.height} };

	// rack();
	cue_ball = CueBall(Vector2Add(apex, { 0.0, 3 * rec.height / 5 }));

	// pocket
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

	collision_handler.handle_collision(rail, cue_ball);
}

void Table::handle_input() {
	cue_ball.handle_input();
}