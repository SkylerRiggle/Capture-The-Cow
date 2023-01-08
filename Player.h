#pragma once

#include "raylib.h"
#include "Beam.h"
#include <corecrt_math.h>
#include <stdio.h>
#include "Math.h"

class Player 
{
public:
	Player(float startX, float startY, bool isPlayerOne) 
	{
		x = startX;
		y = startY;
		Image image;

		if (isPlayerOne) 
		{
			up = KEY_W;
			down = KEY_S;
			left = KEY_A;
			right = KEY_D;

			image = LoadImage("assets/p1.png");
			beamColor = RED;
		}
		else 
		{
			up = KEY_UP;
			down = KEY_DOWN;
			left = KEY_LEFT;
			right = KEY_RIGHT;

			image = LoadImage("assets/p2.png");
			beamColor = BLUE;
		}

		sprite = LoadTextureFromImage(image);
		UnloadImage(image);
		swo = sprite.width / 2.0f;
		sho = sprite.height / 2.0f;
	}

	void Update(float delta, Player* op) 
	{
		// Initial input values
		float inputX = 0;
		float inputY = 0;

		// X input
		if(IsKeyDown(right)) inputX++;
		if(IsKeyDown(left)) inputX--;

		// Y input
		if(IsKeyDown(up)) inputY--;
		if(IsKeyDown(down)) inputY++;

		// Acceleration
		float acc = acceleration * delta;
		if (inputX != 0) 
		{
			currentSpeedX = Lerp(currentSpeedX, maxSpeed * inputX, acc);
			angle = Lerp(angle, 15 * inputX, acc);
		} 
		else 
		{
			currentSpeedX = Lerp(currentSpeedX, 0.0f, acc);
			angle = Lerp(angle, 0.0f, acc);
		}

		if (inputY != 0)
		{
			currentSpeedY = Lerp(currentSpeedY, maxSpeed * inputY, acc);
		}
		else
		{
			currentSpeedY = Lerp(currentSpeedY, 0.0f, acc);
		}

		// Movement
		x += currentSpeedX * delta;
		y += currentSpeedY * delta;

		// Screen edge collisions
		if (x > 800 - swo) { x = 800 - swo; currentSpeedX *= -1; }
		else if (x < swo) { x = swo; currentSpeedX *= -1; }
		if (y > 450 - sho) { y = 450 - sho; currentSpeedY *= -1; }
		else if (y < sho) { y = sho; currentSpeedY *= -1; }

		// Other player collisions
		if (sqrtf(powf(x - (*op).x, 2) + powf(y - (*op).y, 2)) <= colRadius) 
		{
			(*op).currentSpeedX = currentSpeedX;
			(*op).currentSpeedY = currentSpeedY;
			currentSpeedX *= -1;
			currentSpeedY *= -1;

			x += currentSpeedX * delta;
			y += currentSpeedY * delta;
			(*op).x += (*op).currentSpeedX * delta;
			(*op).y += (*op).currentSpeedY * delta;
		}

		// Beam stuff :P
		beam.Update(x, y + 35, angle);
	}

	void Draw(float delta)
	{
		float cosine = cosf(delta) * 5;
		DrawTexturePro(sprite, { 0,0,swo * 2,sho * 2 }, { x,y + cosine,swo * 2,sho * 2 }, { swo,sho }, angle, WHITE);
	}

	void DrawEffect(float delta) 
	{
		float cosine = cosf(delta) * 5;
		beam.Draw(beamColor, cosine);
		DrawEllipse((int)x, (int)y + 50, 18 + cosine, 8 + cosine, { 0,0,0,100 });
	}

	float x = 0, y = 0, currentSpeedX = 0, currentSpeedY = 0;
private:
	const float maxSpeed = 500, acceleration = 1, colRadius = 30;
	float swo = 0, sho = 0, angle = 0;
	int up, down, left, right;
	Texture2D sprite;

	Beam beam = Beam();
	Color beamColor = WHITE;
};