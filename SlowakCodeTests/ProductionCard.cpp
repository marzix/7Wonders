#include "ProductionCard.h"
//br¹zowa i szara karta

ProductionCard::ProductionCard( eCardType cardType, short int epoque, Cost cost, eMaterial _material, int amt )
: Card( cardType, epoque, cost )
{
    if( type == BROWN )
        cardCode = "1";
    else
        cardCode = "2";
    producedMaterial.material = _material;
    producedMaterial.amount = amt;
    displayString += "\n|Material:\t\t|\n|\t" + producedMaterial.GetDisplayInfo() + "-------------------------\n";
}

void ProductionCard::DisplayCard()
{
    cout << displayString;
}

SingleCost ProductionCard::GetProducedMaterial()const
{
    return producedMaterial;
}