#ifndef _BONUS_CARD_H_
#define _BONUS_CARD_H_
#include "Card.h"

//z³ota karta
class BonusCard: public Card
{
public:
    BonusCard( eCardType type, short int epoque, Cost cost, eFreebuild free, eCardType affected, int gold, int points );
    BonusCard( eCardType type, short int epoque, Cost cost, eFreebuild free, int gold );
    void DisplayCard()override {};

private:
    int points = 0;
    eCardType affectedCard = NONE;
    int gold = 0;
    eFreebuild freebuild = EMPTY;
};

#endif