#include "raylib.h"
#include "Game.h"

int main(void)
{
    // Set the screen width, height, and background color
    const int screenWidth = 800;
    const int screenHeight = 450;
    const Color backgroundColor = Color {90, 106, 75, 255};

    // Initialize a window and set the game's target fps
    InitWindow(screenWidth, screenHeight, "Capture The Cow");
    SetTargetFPS(60);

    Player redPlayer = Player(PlayerId::P1, 50, 50);
    
    // Main game loop
    while (!WindowShouldClose())
    {
        // Update
        redPlayer.Update();

        // Draw
        BeginDrawing();
            // Clear the background (screen clearing)
            ClearBackground(backgroundColor);
            redPlayer.Draw();
        EndDrawing();
    }

    // Close the window and exit the program
    CloseWindow();
    return 0;
}
