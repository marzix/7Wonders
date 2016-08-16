#include "ScienceCard.h"

ScienceCard::ScienceCard( eCardType type, short int epoque, Cost cost, eScienceSymbol smb, eFreebuild free )
: Card( type, epoque, cost )
, symbol( smb )
, freebuild( free )
{
    string fb = "\t|\n-------------------------\n";
    string text = GetFreebuildString( freebuild );
    if( text.length() < 8 )
        text += "\t";
    if( freebuild != EMPTY )
        fb = "\t|\n|Freebuild symbol:\t|\n|\t" + text + fb;
    displayString += "\n|Symbol: " + GetScienceSymbolString( symbol ) + fb;
}

void ScienceCard::DisplayCard()
{
    cout << displayString;
}

eFreebuild ScienceCard::GetFreebuildSymbol()const
{
    return freebuild;
}

eScienceSymbol ScienceCard::GetScienceSymbol()const
{
    return symbol;
}