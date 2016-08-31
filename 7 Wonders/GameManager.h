#ifndef _GAME_MANAGER_H_
#define _GAME_MANAGER_H_

#include "Card.h"
#include "xml/rapidxml.hpp"
#include "Player.h"

class GameManager
{
public:
    static GameManager & GetSingleton();
    bool LoadRecources();
    Cost UploadCost( rapidxml::xml_node<char> * node );
    void UploadProductionCards( rapidxml::xml_node<char> * node, eCardType type );
    void UploadMilitaryCards( rapidxml::xml_node<char> * node );
    void UploadScienceCards( rapidxml::xml_node<char> * node );
    void UploadArchitectureCards( rapidxml::xml_node<char> * node );
    void UploadGoldCards( rapidxml::xml_node<char> * node );
    void UploadIndustryCards( rapidxml::xml_node<char> * node, short int epoque, Cost cost );
    void UploadBonusCards( rapidxml::xml_node<char> * node, short int epoque, Cost cost, eFreebuild free );
    void UploadGuildCards( rapidxml::xml_node<char> * node );
    void UploadWonderCards( rapidxml::xml_node<char> * node );

    void DisplayCards( vector<CardPtr> cards )const;
    void DisplayData( vector<CardPtr> cards );
    void StartGame( char* argv[] );
    vector<CardPtr> DrawCardSet();
    void DrawCard( vector<CardPtr> & currentSet );
    int InterpretChoice( const string choice );
    void SellCard( int card, vector<CardPtr> & currentSet );
    bool CollectCard( int card, vector<CardPtr> & currentSet );

    void SaveWinnersTurns();

private:
    vector<CardPtr> usedCards;
    vector<CardPtr> firstEpoqueCards;
    vector<CardPtr> secondEpoqueCards;
    vector<CardPtr> thirdEpoqueCards;

    PlayerPtr firstPlayer;
    PlayerPtr secondPlayer;
    PlayerPtr activePlayer;
    int epoque = 1;

    static GameManager Game;
};

#endif