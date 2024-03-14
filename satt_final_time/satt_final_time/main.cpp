#pragma once

// Please note that this simulation is a 1/25000th scale of Earth
#include "earth.h"
#include "satellite.h"

#include <iostream>
#include <vector>
#include <cmath>

#include "raylib.h"

#include "rlgl.h"
#include "raymath.h";

typedef struct {
	Rectangle rect;
	const char* text;
	Color color;
	Color textcolor;
	bool clicked;
}Button;

bool check_collision(Vector2 point, Rectangle rec)
{
	if (point.x >= rec.x && point.x <= (rec.x + rec.width) && point.y >= rec.y && point.y <= (rec.y + rec.height))
	{
		return false;
	}

	return true;
}




int main()
{
	InitWindow(1600, 1200, "Sattellite Simulator");
	SetWindowState(FLAG_VSYNC_HINT);


	Button play_button = {
	  Rectangle{700.0f,500.0f,400.0f,150.0f},
	  "Play",
	 WHITE,
	 BLACK,
	 false
	};

	Button about_button = {
		Rectangle{700.0f,700.0f,400.0f,150.0f},
		"How to Play",
		WHITE,
		BLACK,
		false
	};

	Button back_button = {
	Rectangle{100.0f,1000.0f,150.0f,80.0f},
	"<--",
	RED,
	BLACK,
	false
	};


	Texture2D Background = LoadTexture("resources/background.png");

	bool menu = true, about = true, back = true;

	const double gm = 6.67e-11;

	Camera2D cam = { 0 };
	cam.zoom = 1;

	// creates Earth object with all its properties
	Earth earth(GetScreenWidth() / 2.0f, GetScreenHeight() / 2.0f);

	//creating a vector so we can dynamically store multiple satellite objects
	std::vector<Satellite> satt_vector;
	std::vector<Satellite> visual_vector;

	float temp, distance_satt;
	int num_of_satts = 0;

	std::cout << "How many sattellites do you want?" << std::endl;
	std::cin >> num_of_satts;

	// get user inputed data for satellites
	for (int i = 0; i < num_of_satts; i++)
	{
		std::cout << "What is the radius of sattellite number " << i + 1 << ": " << std::endl;
		std::cin >> temp;

		std::cout << "What is the distance from the Earth for sattellite number " << i + 1 << ": " << std::endl;
		std::cin >> distance_satt;

		float act_distance = distance_satt * 1000;
		float semi_major_axis = act_distance + earth.get_radius();

		satt_vector.push_back(Satellite((temp / 25000), semi_major_axis));
		visual_vector.push_back(Satellite(15, semi_major_axis));

	}


	float true_anomaly = 90;
	float new_anomaly = 0;

	int counter = 2;
	int setter = 0;

	bool pauser = false;
	// GAME LOOP 
	while (!WindowShouldClose())
	{
		if (menu == true)
		{

			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				Vector2 mouse_pos = GetMousePosition();
				menu = check_collision(mouse_pos, play_button.rect);
				about = check_collision(mouse_pos, about_button.rect);

			}

			BeginDrawing();
			ClearBackground(BLACK);
			DrawTexture(Background, 0, 0, WHITE);

			DrawRectangleRec(play_button.rect, play_button.color);
			DrawText(play_button.text, play_button.rect.x + 115, play_button.rect.y + 40, 80, play_button.textcolor);

			DrawText("Orbital Simulator", 450, 300, 100, WHITE);

			DrawRectangleRec(about_button.rect, about_button.color);
			DrawText(about_button.text, about_button.rect.x + 10, about_button.rect.y + 40, 60, about_button.textcolor);

			EndDrawing();
		}
		if (about == false)
		{
			menu = false;
			if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			{
				Vector2 mouse_pos = GetMousePosition();
				back = check_collision(mouse_pos, back_button.rect);
			}
			BeginDrawing();
			ClearBackground(BLACK);
			DrawTexture(Background, 0, 0, WHITE);

			DrawText("Left-click to zoom in, right click to toggle between satellite\n marker and actual size of sattelite.\n Press M to reset camera view.\nPress 1,2,3,4 to toggle between satellites to zoom into.", 10, 10, 50, WHITE);

			DrawRectangleRec(back_button.rect, back_button.color);
			DrawText(back_button.text, back_button.rect.x + 20, back_button.rect.y + 20, 60, back_button.textcolor);
			EndDrawing();

			if (back == false)
			{
				menu = true;
				about = true;
				back = true;

			}
		}
		if (menu == false && about == true)
		{



			BeginDrawing();
			ClearBackground(BLACK);
			// counter is used to determine whether satellites should be actual size or increased size for visual clarity
			if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
			{
				counter++;
			}
			// resets camera view for when you zoom in all the way and want to get out 
			if (IsKeyPressed(KEY_M))
			{
				cam.zoom = 1;
				cam.offset.x = 0;
				cam.offset.y = 0;
			}

			// Setter is used so program knows which satellite to focus on 
			if (IsKeyPressed(KEY_ONE))
			{
				setter = 0;
			}
			if (IsKeyPressed(KEY_TWO))
			{
				setter = 1;
			}
			if (IsKeyPressed(KEY_THREE))
			{
				setter = 2;
			}
			if (IsKeyPressed(KEY_FOUR))
			{
				setter = 3;
			}

			// Camera zooms in and focuses satellite to center of the screen
			if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
			{
				pauser = true;
				cam.zoom += 1.0f;

				cam.offset.x = 800.0f - satt_vector[setter].get_x() * cam.zoom;
				cam.offset.y = 600.0f - satt_vector[setter].get_y() * cam.zoom;

			}
			else {
				pauser = false;
			}

			BeginMode2D(cam);

			// Draw satellites
			for (size_t i = 0; i < satt_vector.size(); i++)
			{
				if (pauser == false)
				{
					satt_vector[i].calculate_pos(true_anomaly);
				}
				satt_vector[i].Draw();
			}
			// draws out increased size satellites
			if (counter % 2 == 0)
			{
				for (size_t i = 0; i < satt_vector.size(); i++)
				{
					if (pauser == false)
					{
						visual_vector[i].calculate_pos(true_anomaly);
					}
					visual_vector[i].Draw();
				}
			}

			earth.Draw();

			EndMode2D();

			DrawText("Left-click to zoom in, right click to toggle between satellite marker and actual size of sattelite\n Press M to reset camera view", 10, 10, 30, WHITE);

			EndDrawing();
		}
	}
	
	CloseWindow();
}


