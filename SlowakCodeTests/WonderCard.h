#ifndef _WONDER_CARD_H_
#define _WONDER_CARD_H_
#include "Card.h"

class WonderCard: public Card
{
public:
    WonderCard( eCardType, Cost cost, int points, int gold, int military, vector<eBonusType> bonuses, vector<eMaterial> materials );
    void DisplayCard()override {};

private:
    vector<eBonusType> bonuses;
    vector<eMaterial> materials;
    int gold = 0;
    int points = 0;
    int militaryStrength = 0;
};

#endif