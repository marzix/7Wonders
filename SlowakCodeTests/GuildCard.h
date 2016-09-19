#ifndef _GUILD_CARD_H_
#define _GUILD_CARD_H_
#include "Card.h"

//fioletowa karta
class GuildCard: public Card
{
public:
    GuildCard( eCardType type, short int epoque, Cost cost, vector<eCardType> affected, int points, int gold );
    void DisplayCard()override {};

private:
    vector<eCardType> affectedCards;
    int points = 0;
    int gold = 0;
};

#endif