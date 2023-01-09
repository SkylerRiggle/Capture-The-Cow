#pragma once
#include <raylib.h>

class Goal 
{
public:
	Goal(bool isPlayerOne, int newX, int newY) 
	{
		Image image;
		if (isPlayerOne) 
		{
			image = LoadImage("assets/redgoal.png");
		}
		else 
		{
			image = LoadImage("assets/bluegoal.png");
		}

		x = newX;
		y = newY;
		sprite = LoadTextureFromImage(image);
		UnloadImage(image);
		swo = sprite.width / 2;
		sho = sprite.height / 2;
	}

	void Draw() 
	{
		DrawTexture(sprite, x - swo, y - sho, WHITE);
	}

	int x, y;
private:
	int swo, sho;
	Texture2D sprite;
};