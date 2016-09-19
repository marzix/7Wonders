#include "WonderCard.h"

WonderCard::WonderCard( eCardType type, Cost cost, int p, int g, int military, vector<eBonusType> bonus, vector<eMaterial> mat )
: Card( type, cost )
, points( p )
, gold( g )
, militaryStrength( military )
, bonuses( bonus )
, materials( mat )
{}