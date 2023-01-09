#pragma once

#include "raylib.h"
#include "Player.h"
#include "CowManager.h"
#include <string>
#include "Button.h"
#include "Goal.h"
#include "Score.h"

class GameManager 
{
public:
	void Run() 
	{
		Image image = LoadImage("assets/banner.png");
		banner = LoadTextureFromImage(image);
		UnloadImage(image);

		PlayMusicStream(music);
		float delta = 0;

		while (isRunning)
		{
			isRunning = !WindowShouldClose();
			UpdateMusicStream(music);
			delta = GetFrameTime();
			isInGame ? UpdateGame(delta) : UpdateMenu(delta);
			BeginDrawing();
				ClearBackground(backgroundColor);
				isInGame ? DrawGame() : DrawMenu();
			EndDrawing();
		}

		CloseGame();
	}

	void InitGame()
	{
		p1.currentSpeedX = 0;
		p1.currentSpeedY = 0;
		p2.currentSpeedX = 0;
		p2.currentSpeedY = 0;

		p1.x = 75;
		p2.x = 725;
		p1.y = 225;
		p2.y = 225;

		currentMatchTime = (float)matchLength;
		isInGame = true;
		isPlaying = true;
	}

	void CloseGame()
	{
		UnloadMusicStream(music);
		CloseAudioDevice();
		CloseWindow();
	}

private:
	std::string GetTime(float time)
	{
		int min = (int)(time / 60);
		int sec = (int)(time - (60 * min));

		return std::to_string(min) + ":" + (sec < 10 ? "0" : "") + std::to_string(sec);
	}

	std::string GetScore(int score)
	{
		if (score < 10) return "0" + std::to_string(score);
		else return std::to_string(score);
	}

    void UpdateMenu(float delta)
    {
		int play = playButton.Update();
		if (play == 1) InitGame();
		int exit = exitButton.Update();
		if (exit == 2) isRunning = false;
    }

    void DrawMenu()
    {
		DrawTextureEx(banner, { 0,0 }, 0, 0.25, WHITE);
		DrawText("Capture The Cow!", 42, 92, 62, BLACK);
		DrawText("Capture The Cow!", 50, 100, 60, WHITE);
		playButton.Draw();
		exitButton.Draw();
		DrawText("Malorie & Skyler Riggle | 2023", 10, 435, 12, WHITE);
    }

    void UpdateGame(float delta) 
    {
		if (isPlaying) 
		{
			currentMatchTime -= delta;

			if (currentMatchTime <= 0)
			{
				currentMatchTime = 0;
				isPlaying = false;
			}

			p1.Update(delta, &p2);
			p2.Update(delta, &p1);

			Beam* b1 = &p1.beam;
			Beam* b2 = &p2.beam;
			ScorePackage score = cowManager.Update(delta, b1, b2, &g1, &g2);

			if (score.isPlayerOne) 
			{
				p1Score += score.scoreValue;
			}
			else 
			{
				p2Score += score.scoreValue;
			}
		}
		else if (IsKeyPressed(KEY_R))
		{
			InitGame();
		}
    }

    void DrawGame() 
    {
		g1.Draw();
		g2.Draw();

		cowManager.Draw();

		p1.DrawEffect(currentMatchTime);
		p2.DrawEffect(currentMatchTime);
		p1.Draw(currentMatchTime);
		p2.Draw(currentMatchTime);

		// Draw UI
		DrawRectangle(325, 0, 150, 60, { 100,0,100,50 });
		DrawRectangleLines(325, 0, 150, 60, WHITE);
		DrawText(GetTime(currentMatchTime).c_str(), 365, 10, 40, WHITE);

		DrawRectangle(475, 0, 80, 50, { 0,0,255,50 });
		DrawRectangleLines(475, 0, 80, 50, BLUE);
		DrawText(GetScore(p2Score).c_str(), 485, 10, 40, BLUE);

		DrawRectangle(245, 0, 80, 50, { 255,0,0,50 });
		DrawRectangleLines(245, 0, 80, 50, RED);
		DrawText(GetScore(p1Score).c_str(), 270, 10, 40, RED);

		if (!isPlaying) 
		{
			DrawText("GAME OVER!", 175, 100, 75, WHITE);
			if (p1Score < p2Score) 
			{
				DrawText("Player 2 Wins", 200, 175, 30, BLUE);
			} 
			else if (p1Score > p2Score) 
			{
				DrawText("Player 1 Wins", 200, 175, 30, RED);
			} 
			else 
			{
				DrawText("Draw", 200, 175, 30, WHITE);
			}
			DrawText("Press 'R' to Restart", 200, 210, 30, WHITE);
		}
    }

	const Music music = LoadMusicStream("assets/music.mp3");

	const Color backgroundColor = Color{ 90, 106, 75, 255 };
	bool isRunning = true, isInGame = false, isPlaying = false;

	Button playButton = Button(1, 650, 300);
	Button exitButton = Button(2, 650, 360);

	CowManager cowManager = CowManager();

	Player p1 = Player(75, 225, true);
	Player p2 = Player(725, 225, false);

	Goal g1 = Goal(true, 75, 225);
	Goal g2 = Goal(false, 725, 225);
	int p1Score = 0, p2Score = 0;
	float currentMatchTime;
	const int matchLength = 120; // In seconds

	Texture2D banner;
};