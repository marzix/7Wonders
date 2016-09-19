#include "BonusCard.h"

BonusCard::BonusCard( eCardType type, short int epoque, Cost cost, eFreebuild free, eCardType affected, int g, int p )
: Card( type, epoque, cost )
, affectedCard( affected )
, gold( g )
, points( p )
, freebuild( free )
{}

BonusCard::BonusCard( eCardType type, short int epoque, Cost cost, eFreebuild free, int g )
: Card( type, epoque, cost )
, gold( g )
, freebuild( free )
{}