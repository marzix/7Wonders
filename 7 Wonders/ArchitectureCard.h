#ifndef _ARCHITECTURE_CARD_H_
#define _ARCHITECTURE_CARD_H_
#include "Card.h"

//niebieska karta
class ArchitectureCard: public Card
{
public:
    ArchitectureCard( eCardType type, short int epoque, Cost cost, int points, eFreebuild free );
    void DisplayCard()override;
    eFreebuild GetFreebuildSymbol()const;

private:
    int points = 0;
    eFreebuild freebuild = EMPTY;
};

#endif