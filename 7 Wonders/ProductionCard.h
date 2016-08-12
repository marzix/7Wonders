#ifndef _PRODUCTION_CARD_H_
#define _PRODUCTION_CARD_H_
#include "Card.h"

//szara i br¹zowa karta
class ProductionCard: public Card
{
public:
    ProductionCard( eCardType cardType, short int epoque, Cost cost, eMaterial material, int amount );
    void DisplayCard()override;
    SingleCost GetProducedMaterial()const;

private:
    /*eMaterial producedMaterial;
    int amount = 0;*/
    SingleCost producedMaterial;
};

#endif