#include "Game.h"
#include "raylib.h"

Player::Player(PlayerId id, int startX, int startY) 
{
	// Initialize the correct player's attributes
	switch (id)
	{
	case PlayerId::P1:
		break;
	case PlayerId::P2:
		break;
	default:
		delete this;
		return;
	}

	// Common player initialization
	this->x = startX;
	this->y = startY;
}

void Player::Update() 
{
	if (IsKeyDown(KEY_W)) {
		this->y -= 5;
	}
	else if (IsKeyDown(KEY_S)) {
		this->y += 5;
	}
}

void Player::Draw() 
{
	DrawRectangle(this->x, this->y, 30, 10, RED);
}