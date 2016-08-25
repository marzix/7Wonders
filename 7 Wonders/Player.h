#include "Constants.h"
#include "Card.h"

class Player;
using PlayerPtr = shared_ptr<Player>;

class Player
{
public:
    Player() = default;
    Player( string name );

    string GetName()const;
    int GetGold()const;
    void CollectCard( CardPtr card, Cost costLeft );
    void AddGold( int g );
    bool CheckIfAfordable( Cost & cardCost );
    void DisplayCards();
    int GetTotalPoints();
    int GetMilitaryStrength();
    void SaveTurn( int epoque, vector<CardPtr> cards, unsigned points, unsigned choice );
    string GetCourseOfGame()const;

private:
    string name;
    string courseOfGameText;
    vector<CardPtr> cards;
    int gold = 10;
};