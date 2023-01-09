#include "GameManager.h"

int main(void)
{
    InitWindow(800, 450, "Capture The Cow");
    InitAudioDevice();
    SetTargetFPS(60);

    Image icon = LoadImage("assets/spot.png");
    SetWindowIcon(icon);
    UnloadImage(icon);

    GameManager gameManager = GameManager();
    gameManager.Run();
    return 0;
}
