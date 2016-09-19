#ifndef _MILITARY_CARD_H_
#define _MILITARY_CARD_H_
#include "Card.h"

//czerwona karta
class MilitaryCard: public Card
{
public:
    MilitaryCard( eCardType type, short int epoque, Cost cost, int stren, eFreebuild free );
    void DisplayCard()override;
    eFreebuild GetFreebuildSymbol()const;
    int GetPoints()const;

private:
    int strength = 1;
    eFreebuild freebuild = EMPTY;
};

#endif