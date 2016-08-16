#include "MilitaryCard.h"

MilitaryCard::MilitaryCard( eCardType type, short int epoque, Cost cost, int stren, eFreebuild free )
: Card( type, epoque, cost )
, strength( stren )
, freebuild( free )
{
    string fb = "\n";
    if( freebuild != EMPTY )
    {
        fb = "\n|Freebuild symbol:\t|\n|\t";
        string text = GetFreebuildString( freebuild ) + "\t";
        if( text.length() < 9 )
            text += "\t";
        fb += text + "|\n";
    }
    displayString += "\n|Military points: " + std::to_string( strength ) + "\t|" + fb + "-------------------------\n";
}

void MilitaryCard::DisplayCard()
{
    cout << displayString;
}

eFreebuild MilitaryCard::GetFreebuildSymbol()const
{
    return freebuild;
}

int MilitaryCard::GetPoints()const
{
    return strength;
}