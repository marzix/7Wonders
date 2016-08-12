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
    void CollectCard( CardPtr card );
    void AddGold( int g );
    bool CheckIfAfordable( Cost & cardCost );
    void DisplayCards();
    int GetTotalPoints()const;

private:
    string name;
    vector<CardPtr> cards;
    int gold = 10;
};