#include "raylib.h"
#include "Player.h"
#include <string>

std::string GetTime(float time)
{
    int min = time / 60;
    int sec = time - (60 * min);

    return std::to_string(min) + ":" + (sec < 10 ? "0" : "") + std::to_string(sec);
}

std::string GetScore(int score) 
{
    if (score < 10) return "0" + std::to_string(score);
    else return std::to_string(score);
}

int main(void)
{
    // Set the screen width, height, and background color
    const int screenWidth = 800;
    const int screenHeight = 450;
    const Color backgroundColor = Color {90, 106, 75, 255};

    // Initialize a window and set the game's target fps
    InitWindow(screenWidth, screenHeight, "Capture The Cow");
    SetTargetFPS(60);

    InitAudioDevice();

    Player p1 = Player(75, 225, true);
    Player p2 = Player(725, 225, false);
    int p1Score = 0, p2Score = 0;

    Music music = LoadMusicStream("assets/music.mp3");
    PlayMusicStream(music);

    // Main game loop
    float delta = 0;
    float matchTime = 120;
    while (!WindowShouldClose())
    {
        // Update
        delta = GetFrameTime();
        matchTime -= delta;

        if (matchTime <= 0) 
        {
            matchTime = 0;
        }

        UpdateMusicStream(music);

        p1.Update(delta, &p2);
        p2.Update(delta, &p1);

        // Draw
        BeginDrawing();
            // Clear the background (screen clearing)
            ClearBackground(backgroundColor);

            // Draw the scene
            p1.DrawEffect(matchTime);
            p2.DrawEffect(matchTime);
            p1.Draw(matchTime);
            p2.Draw(matchTime);

            // Draw UI
            DrawRectangle(325, 0, 150, 60, { 100,0,100,50 });
            DrawRectangleLines(325, 0, 150, 60, WHITE);
            DrawText(GetTime(matchTime).c_str(), 365, 10, 40, WHITE);

            DrawRectangle(475, 0, 80, 50, { 255,0,0,50 });
            DrawRectangleLines(475, 0, 80, 50, RED);
            DrawText(GetScore(p1Score).c_str(), 485, 10, 40, RED);

            DrawRectangle(245, 0, 80, 50, { 0,0,255,50 });
            DrawRectangleLines(245, 0, 80, 50, BLUE);
            DrawText(GetScore(p2Score).c_str(), 270, 10, 40, BLUE);

        EndDrawing();
    }

    UnloadMusicStream(music);
    CloseAudioDevice();

    // Close the window and exit the program
    CloseWindow();
    return 0;
}
