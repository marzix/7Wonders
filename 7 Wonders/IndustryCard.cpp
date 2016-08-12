#include "IndustryCard.h"

IndustryCard::IndustryCard( eCardType type, short int epoque, Cost cost, vector<eMaterial> material, eBonusType b )
: Card( type, epoque, cost )
, materials( material )
, bonus( b )
{}