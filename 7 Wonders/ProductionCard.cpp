#include "ProductionCard.h"

ProductionCard::ProductionCard( eCardType cardType, short int epoque, Cost cost, eMaterial _material, int amt )
: Card( cardType, epoque, cost )
{
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