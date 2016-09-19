#ifndef _SCIENCE_CARD_H_
#define _SCIENCE_CARD_H_
#include "Card.h"

//zielona karta
class ScienceCard: public Card
{
public:
    ScienceCard( eCardType type, short int epoque, Cost cost, eScienceSymbol smb, eFreebuild free );
    void DisplayCard()override;
    eFreebuild GetFreebuildSymbol()const;
    eScienceSymbol GetScienceSymbol()const;

private:
    eScienceSymbol symbol;
    eFreebuild freebuild = EMPTY;
};

#endif