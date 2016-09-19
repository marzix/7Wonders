#include "GuildCard.h"

GuildCard::GuildCard( eCardType type, short int epoque, Cost cost, vector<eCardType> affected, int p, int g )
: Card( type, epoque, cost )
, affectedCards( affected )
, points( p )
, gold( g )
{}