#include <iostream>
#include "GameManager.h"
#include "AIWonder.h"
/*parametry wejœciowe:
nazwa_programu.exe typ_gracza1 typ_gracza2

typ gracza:
h - cz³owiek (HUMAN)
a - sztuczna inteligencja (AI)
*/


int main(int argc, char* argv[])
{
	char* arg[3] = { "", "a", "h" };
	bool ifAI = false;
	if (argc == 3)
	{
		arg[1] = argv[1];
		arg[2] = argv[2];

	}
	if (!strcmp(arg[1], "a") || !strcmp(arg[2], "a"))
		ifAI = true;
	if (ifAI)
	{
		AIWonder::getSingleton().initAI();
	}
	GameManager Game = GameManager::GetSingleton();
	Game.LoadRecources();
	Game.StartGame(arg);
	return 0;
}