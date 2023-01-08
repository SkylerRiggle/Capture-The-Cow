#pragma once

class Beam 
{
public:
	Beam() 
	{
		Image image = LoadImage("assets/beam.png");
		sprite = LoadTextureFromImage(image);
		UnloadImage(image);

		swo = sprite.width / 2.0f;
		sho = sprite.height / 2.0f;
	}

	void Update(float newX, float newY, float newAngle) 
	{
		x = newX;
		y = newY;
		angle = newAngle;
	}

	void Draw(Color color, float cosine) 
	{
		DrawTexturePro(sprite, { 0,0,swo * 2,sho * 2 }, { x,y + cosine - sho,swo * 2,sho * 2 }, { swo,0 }, angle, color);
	}
	
	float x = 0, y = 0;
private:
	float swo = 0, sho = 0, angle = 0;
	Texture2D sprite;
};