#include <iostream>
#include "GameManager.h"

/*parametry wejœciowe: 
    nazwa_programu.exe typ_gracza1 typ_gracza2

typ gracza:
    h - cz³owiek (HUMAN)
    a - sztuczna inteligencja (AI)
*/

int main( int argc, char* argv[] )
{
    char* arg[3] = { "", "h", "h" };
    if( argc == 3 )
    {
        arg[1] = argv[1];
        arg[2] = argv[2];
    }
    GameManager Game = GameManager::GetSingleton();
    Game.LoadRecources();
    Game.StartGame( arg );
    return 0;
}