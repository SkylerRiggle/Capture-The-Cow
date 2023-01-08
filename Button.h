#pragma once

class Button 
{
public:
	Button(int newID, int x, int y) 
	{
		switch (newID)
		{
		case 1:
			text = "Play";
			break;
		case 2:
			text = "Exit";
			break;
		default:
			text = "ERROR";
			break;
		}

		id = newID;
		posX = x;
		posY = y;
	}

	int Update() 
	{
		Vector2 mousePos = GetMousePosition();

		if (mousePos.x >= posX && mousePos.x <= posX + 100 && mousePos.y >= posY && mousePos.y <= posY + 50) 
		{
			color = { 255,255,255,100 };

			if (IsMouseButtonPressed(0)) 
			{
				return id;
			}
		}
		else 
		{
			color = { 255,255,255,50 };
		}

		return -1;
	}

	void Draw() 
	{
		DrawRectangle(posX, posY, 100, 50, color);
		DrawRectangleLines(posX, posY, 100, 50, WHITE);
		DrawText(text, posX + 10, posY + 5, 40, BLACK);
	}

private:
	int id, posX = 0, posY = 0;
	Color color = { 255,255,255,50 };
	const char* text;
};