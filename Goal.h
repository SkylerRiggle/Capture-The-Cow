#pragma once
#include <raylib.h>

class Goal 
{
public:
	Goal(bool isPlayerOne, int x, int y) 
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

		posX = x;
		posY = y;
		sprite = LoadTextureFromImage(image);
		UnloadImage(image);
		swo = sprite.width / 2;
		sho = sprite.height / 2;
	}

	void Draw() 
	{
		DrawTexture(sprite, posX - swo, posY - sho, WHITE);
	}

private:
	int posX, posY, swo, sho;
	Texture2D sprite;
};