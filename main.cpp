#include "GameManager.h"

int main(void)
{
    InitWindow(800, 450, "Capture The Cow");
    InitAudioDevice();
    SetTargetFPS(60);

    GameManager gameManager = GameManager();
    gameManager.Run();
    return 0;
}
