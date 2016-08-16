#include "ArchitectureCard.h"

ArchitectureCard::ArchitectureCard( eCardType type, short int epoque, Cost cost, int p, eFreebuild free )
: Card( type, epoque, cost )
, points( p )
, freebuild( free )
{
    displayString += "\n|Points: " + std::to_string( points ) + "\t\t|\n-------------------------\n";
}

void ArchitectureCard::DisplayCard()
{
    cout << displayString;
}

eFreebuild ArchitectureCard::GetFreebuildSymbol()const
{
    return freebuild;
}

int ArchitectureCard::GetPoints()const
{
    return points;
}