#include "raylib.h"

#include <iostream>

// We will be using metric system because that's what SpaceX and Nasa use cause it's scientific standard
// Earth radius = 6371007.2 meters, use 1/25000th scale 
class Earth
{
private:
	float x, y;
	float radius;
	float mass;
public:

	Earth(float ex, float why)
	{

		x = ex;
		y = why;
		radius = 6.38e6;
		mass = 5.97e24;

	}

	const float get_radius() { return radius; }
	const float get_mass() { return mass; }

	void Draw()
	{
		DrawCircle((int)x, (int)y, (radius / 25000), BLUE);
	}
};