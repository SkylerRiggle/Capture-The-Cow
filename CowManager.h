#pragma once

#include "Cow.h"
#include <vector>
#include "Goal.h"
#include "Score.h"

class CowManager 
{
public:
	void SpawnCow() 
	{
		float spawnX = (maxX - minX) * ((rand() % 100) / 100.0f) + minX;
		float spawnY = (maxY - minY) * ((rand() % 100) / 100.0f) + minY;
		int score = rand() % 100;

		Cow newCow;
		if (score >= 0 && score < 50) 
		{
			newCow = Cow(1, spawnX, spawnY);
		} 
		else if (score >= 50 && score < 75) 
		{
			newCow = Cow(2, spawnX, spawnY);
		} 
		else if (score >= 75 && score < 90) 
		{
			newCow = Cow(3, spawnX, spawnY);
		} 
		else 
		{
			newCow = Cow(5, spawnX, spawnY);
		}

		newCow.currentSpeedY = 250;
		newCow.currentSpeedX = (rand() % 100) - 50.0f;
		cows.push_back(newCow);
	}
	
	ScorePackage Update(float delta, Beam* b1, Beam* b2, Goal* g1, Goal* g2)
	{
		if (numCows < maxCows && cowTimer >= cowDelay) 
		{
			SpawnCow();
			numCows++;
			cowTimer = 0;
		} 
		else 
		{
			cowTimer += delta;
		}

		ScorePackage returnValue{ true, 0 };
		for (size_t index = 0; index < cows.size(); index++)
		{
			Cow* cow = &cows.at(index);
			int result = (*cow).Update(delta, b1, b2, g1, g2);
			if (result != 0) 
			{
				if (result == 1) 
				{
					returnValue.isPlayerOne = true;
				}
				else if (result == 2)
				{
					returnValue.isPlayerOne = false;
				}

				returnValue.scoreValue = cow->score;
				cows.erase(cows.begin() + index);
				numCows--;
			}
		}

		return returnValue;
	}

	void Draw() 
	{
		for (size_t index = 0; index < cows.size(); index++)
		{
			cows.at(index).Draw();
		}
	}

private:
	const float cowDelay = 2;
	float cowTimer = 0;
	size_t numCows = 0;
	const size_t maxCows = 3;
	const int minX = 300, maxX = 500, minY = 50, maxY = 400;
	std::vector<Cow> cows{};
};