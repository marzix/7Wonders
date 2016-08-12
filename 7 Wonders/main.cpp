#include <iostream>
#include "GameManager.h"

int main()
{
    GameManager Game = GameManager::GetSingleton();
    Game.LoadRecources();
    Game.StartGame();
    return 0;
}