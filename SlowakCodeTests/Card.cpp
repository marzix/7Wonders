#include "Card.h"

Card::Card( eCardType cardType, Cost c )
: type( cardType )
, cost( c )
{
    displayString = "-------------------------\n|\t*" + GetCardTypeString( type ) + "*\t\t|\n" + cost.GetCostString() + "|\t\t\t|";
}

Card::Card( eCardType cardType, short int epq, Cost c )
: type( cardType )
, epoque( epq )
, cost( c )
{
    displayString = "-------------------------\n|\t*" + GetCardTypeString( type ) + "*\t\t|\n" + cost.GetCostString() + "|\t\t\t|";
}

void Card::SetType( eCardType cardType )
{
    type = cardType;
}

void Card::SetCost( vector<SingleCost> mat, eFreebuild free )
{
    cost.materials = mat;
    cost.freebuild = free;
}

void Card::SetEpoque( short int epq )
{
    epoque = epq;
}

eCardType Card::GetCardType()const
{
    return type;
}

Cost Card::GetCost()const
{
    return cost;
}

short int Card::GetEpoque()const
{
    return epoque;
}

string Card::GetDisplayInfo()
{
    return displayString;
}

string Card::GetCardCode()const
{
    return cardCode;
}