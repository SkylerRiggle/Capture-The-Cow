#pragma once

#include "raylib.h"

class Cow 
{
public:
	Cow(int newScore) 
	{
		Image image;
		switch (newScore)
		{
		case 1:
			image = LoadImage("assets/white.png");
			break;
		case 2:
			image = LoadImage("assets/spot.png");
			break;
		case 3:
			image = LoadImage("assets/brown.png");
			break;
		case 5:
			image = LoadImage("assets/strawberry.png");
			break;
		default:
			image = LoadImage("assets/white.png");
			newScore = 1;
			break;
		}

		score = newScore;
		sprite = LoadTextureFromImage(image);
		swo = sprite.width / 2;
		sho = sprite.height / 2;
	}

	void Update() 
	{
	
	}

	void Draw() 
	{
		DrawTextureEx(sprite, { x - swo, y - sho }, 0, 1, WHITE);
	}

	float x = 200, y = 100;
	int score;

private:
	float swo = 0, sho = 0;
	Texture2D sprite;
};