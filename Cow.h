#pragma once

#include "raylib.h"
#include "Math.h"
#include "Goal.h"

class Cow 
{
public:
	Cow(int newScore = 0, float startX = 0, float startY = 0) 
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
		UnloadImage(image);
		swo = sprite.width / 2.0f;
		sho = sprite.height / 2.0f;
		x = startX;
		y = startY;
	}

	int Update(float delta, Beam* b1, Beam* b2, Goal* g1, Goal* g2)
	{
		float d1 = sqrtf(powf((*g1).x - x, 2) + powf((*g1).y - y, 2));
		if (d1 <= 50) { return 1; }
		float d2 = sqrtf(powf((*g2).x - x, 2) + powf((*g2).y - y, 2));
		if (d2 <= 50) { return 2; }

		d1 = sqrtf(powf((*b1).x - x, 2) + powf((*b1).y - y, 2));
		d2 = sqrtf(powf((*b2).x - x, 2) + powf((*b2).y - y, 2));
		if (d1 <= range && d1 < d2)
		{
			targetSpeedX = force * ((*b1).x - x) / d1;
			targetSpeedY = force * ((*b1).y - y) / d1;
		} 
		else if (d2 <= range)
		{
			targetSpeedX = force * ((*b2).x - x) / d2;
			targetSpeedY = force * ((*b2).y - y) / d2;
		} else 
		{
			targetSpeedX = 0;
			targetSpeedY = 0;
		}

		float acc = delta * acceleration;
		currentSpeedX = Lerp(currentSpeedX, targetSpeedX, acc);
		currentSpeedY = Lerp(currentSpeedY, targetSpeedY, acc);

		if (x > 800 - swo) { x = 800 - swo; currentSpeedX *= -1; }
		else if (x < swo) { x = swo; currentSpeedX *= -1; }
		if (y > 450 - sho) { y = 450 - sho; currentSpeedY *= -1; }
		else if (y < sho) { y = sho; currentSpeedY *= -1; }

		x += currentSpeedX * delta;
		y += currentSpeedY * delta;
		return 0;
	}

	void Draw()
	{
		float speedY = fabsf(currentSpeedY);
		DrawEllipse((int)x, (int)(y + speedY + 5), 0.15f * speedY, 0.09f * speedY, { 0,0,0,100});
		DrawTextureRec(sprite, { 0, 0, copysignf(swo * 2, currentSpeedX), sho * 2 }, {x - swo, y - sho}, WHITE);
	}

	float x = 200, y = 100, currentSpeedX = 0, currentSpeedY = 0, targetSpeedX = 0, targetSpeedY = 0;
	int score;

private:
	float swo = 0, sho = 0, acceleration = 1, range = 50, force = 750;
	Texture2D sprite;
};