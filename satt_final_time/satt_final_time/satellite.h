#include "raylib.h"

#include <iostream>


class Satellite
{
private:
	float radius;
	float distance;
	float speed;
	float angle;
	float x = 0, y = 0;
public:
	Satellite(float r, float d)
	{
		radius = r;
		distance = d;

	}

	Satellite()
	{
		radius = 0;
		distance = 0;
		speed = 0;
		angle = 0;
		x = 0;
		y = 0;
	}

	float get_distance() { return distance; }
	float get_speed() { return speed; }
	float get_angle() { return angle; }
	float get_x() { return x; }
	float get_y() { return y; }

	void set_distance(float d) { distance = d; }
	void set_speed(float s) { speed = s; }
	void set_angle(float a) { angle = a; }
	void set_x(float ex) { x = ex; }
	void set_y(float why) { y = why; }

	float calculate_pos(float &true_anomaly);

	void Draw()
	{
		DrawCircle(x, y, (radius), RED);
	}
};


float Satellite::calculate_pos(float &true_anomaly)
{
	float true_ano_rad = 0;
	float new_ano_rad = 0;
	float M_original = 0;
	float real_Mo = 0;
	float new_M = 0;
	float n = 0;

	float curr_angular_position = 0;


	true_anomaly += 0.1;

	true_ano_rad = true_anomaly * (3.14 / 180);
	new_ano_rad = true_anomaly * (3.14 / 180);

	M_original = acos((0.1 + cos(true_ano_rad)) / (1 + 0.1 * cos(true_ano_rad)));

	real_Mo = M_original - 0.1 * sin(M_original);

	n = sqrt((3.9860005e23 / (distance * distance * distance)));


	new_M = real_Mo + n * (GetTime());


	curr_angular_position = (new_M + 2 * 0.1 * sin(new_M) + 1.25 * (0.1 * 0.1) * sin(2 * new_M)) / 25000;


	x = GetScreenWidth() / 2 + (distance / 25000) * sin(curr_angular_position);
	y = GetScreenHeight() / 2 + (distance / 25000) * cos(curr_angular_position);

	return true_anomaly;
}