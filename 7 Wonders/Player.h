#include "Constants.h"
#include "Card.h"

class Player;
using PlayerPtr = shared_ptr<Player>;

class Player
{
public:
    Player() = default;
    Player( string name, char* type );

    void SetPlayerType( ePlayerType );
    ePlayerType GetPlayerType()const;
    string GetName()const;
    int GetGold()const;
    void CollectCard( CardPtr card, Cost costLeft );
    void AddGold( int g );
    bool CheckIfAfordable( Cost & cardCost );
    void DisplayCards();
    int GetTotalPoints();
    int GetMilitaryStrength();
    string SaveTurn( int epoque, vector<CardPtr> cards );
    void SaveTurn( unsigned choice );
    string GetCourseOfGame()const;
	string GetCurrentTurn(int epoque, vector<CardPtr> cards);
	vector<SingleCost> GetOwnedMaterials();
    int GetScienceCardSymbolCount( eScienceSymbol symbol )const;

private:
    string name;
    string courseOfGameText;
    vector<CardPtr> cards;
    int gold = 10;
    ePlayerType playerType;
	vector<SingleCost> ownedMaterials;
};