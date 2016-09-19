#ifndef _CARD_H_
#define _CARD_H_
#include "Constants.h"
#include <vector>
#include <memory>

class Card;
using CardPtr = shared_ptr<Card>;

struct SingleCost
{
    eMaterial material;
    int amount;
    string GetDisplayInfo()
    {
        string text = GetMaterialString( material )+ ": " + std::to_string( amount ) + "\t";
        if( text.length() < 9 )
            text += "\t";
        return  text + "|\n";
    }
};

struct Cost
{
    vector<SingleCost> materials;
    eFreebuild freebuild = EMPTY;

    string GetCostString()
    {
        string cost = "|Cost:\t\t\t|\n";
        if( freebuild != EMPTY )
        {
            string freebuildName = GetFreebuildString( freebuild ) + " or";
            if( freebuildName.length() < 8 )
                freebuildName += "\t";
            cost += "|\t" + freebuildName + "\t|\n";
        }
        if( materials.size() == 0 )
            cost += "|\tfree\t\t|\n";
        for( auto m : materials )
            cost += "|\t" + m.GetDisplayInfo();
        return cost;
    }
};

class Card
{
public:
    Card() = default;
    Card( eCardType type, Cost cost );
    Card( eCardType type, short int epoque, Cost cost );

    void SetType( eCardType type );
    void SetCost( vector<SingleCost> materials, eFreebuild free );
    void SetEpoque( short int epoque );
    eCardType GetCardType()const;
    Cost GetCost()const;
    short int GetEpoque()const;

    virtual void DisplayCard() = 0;
    string GetDisplayInfo();
    string GetCardCode()const;

protected:
    eCardType type = NONE;
    Cost cost;
    short int epoque = 1;
    string displayString;
    string cardCode;
};

#endif