#ifndef _INDUSTRY_CARD_H_
#define _INDUSTRY_CARD_H_
#include "Card.h"

//z³ota karta
class IndustryCard: public Card
{
public:
    IndustryCard( eCardType type, short int epoque, Cost cost, vector<eMaterial> materials, eBonusType bonus );
    void DisplayCard()override {};

private:
    vector<eMaterial> materials;
    eBonusType bonus;
};

#endif