#include "Player.h"
#include "MilitaryCard.h"
#include "ArchitectureCard.h"
#include "ProductionCard.h"
#include "ScienceCard.h"
#include <algorithm>

Player::Player( string _name )
: name( _name )
{}

string Player::GetName()const
{
    return name;
}

int Player::GetGold()const
{
    return gold;
}

void Player::CollectCard( CardPtr card )
{
    Cost cardCost = card->GetCost();
    for( SingleCost sc : cardCost.materials )
    {
        if( sc.material == GOLD && sc.amount < gold )
            gold -= sc.amount;
    }
    cards.push_back( card );
}

void Player::AddGold( int g )
{
    gold += g;
}

bool Player::CheckIfAfordable( Cost & cardCost )
{
    if( cardCost.materials.size() && cardCost.materials[0].material == GOLD )
    {
        if( gold >= cardCost.materials[0].amount )
            cardCost.materials.erase( cardCost.materials.begin() );
        else
            return false;
    }
    for( CardPtr c : cards )
    {
        if( cardCost.freebuild != EMPTY )
        {
            if( c->GetCardType() == RED )
            {
                MilitaryCard* red = dynamic_cast<MilitaryCard*>( c.get() );
                if( red && red->GetFreebuildSymbol() == cardCost.freebuild )
                    return true;
                else
                    continue;
            }
            else if( c->GetCardType() == BLUE )
            {
                ArchitectureCard* blue = dynamic_cast<ArchitectureCard*>( c.get() );
                if( blue && blue->GetFreebuildSymbol() == cardCost.freebuild )
                    return true;
                else
                    continue;
            }
            else if( c->GetCardType() == GREEN )
            {
                ScienceCard* green = dynamic_cast<ScienceCard*>( c.get() );
                if( green && green->GetFreebuildSymbol() == cardCost.freebuild )
                    return true;
                else
                    continue;
            }
        }
        if( c->GetCardType() == BROWN || c->GetCardType() == GREY )
        {
            ProductionCard* brown = dynamic_cast<ProductionCard*>( c.get() );
            if( brown )
            {
                for( unsigned int i = 0; i < cardCost.materials.size(); i++ )
                {
                    if( cardCost.materials[i].material == GOLD )
                    {
                        if( gold >= cardCost.materials[i].amount )
                        {
                            cardCost.materials.erase( cardCost.materials.begin() + i );
                            continue;
                        }
                        else
                            return false;
                    }
                    SingleCost sc = brown->GetProducedMaterial();
                    if( cardCost.materials[i].material == sc.material )
                    {
                        if( sc.amount >= cardCost.materials[i].amount )
                            cardCost.materials.erase( cardCost.materials.begin() + i );
                        else
                            cardCost.materials[i].amount -= sc.amount;
                    }
                }
            }
        }
    }
    if( cardCost.materials.empty() )
        return true;
    else
        return false;
}

void Player::DisplayCards()
{
    if( cards.empty() )
    {
        cout << "\t\t\t\t\t\tYOU DON'T HAVE ANY CARDS\n\n";
        return;
    }
    cout << "\t\t\t\t\t\tYOUR CARDS:\n";
    for( auto card : cards )
    {
        string displayInfo = "\t\t\t\t\t\t" + card->GetDisplayInfo();
        for( unsigned i = 0; i < displayInfo.length(); i++ )
        {
            if( displayInfo[i] == '\n' )
                displayInfo.insert( i + 1, "\t\t\t\t\t\t" );
        }
        cout << displayInfo << endl;
    }
    cout << endl;
}

struct SymbolsCounter
{
    SymbolsCounter( eScienceSymbol s ) : symbol(s) {};

    eScienceSymbol symbol;
    int count = 1;
};

int Player::GetTotalPoints()
{
    //posortuj karty po typie
    //zielone: liczba kart do kwadratu
    //czerwone: si³a militarna = punkty
    //niebieskie: punkty
    //z³oto: 1pkt za ka¿de 3 monety

    std::sort( cards.begin(), cards.end(), []( const CardPtr& c1, const CardPtr& c2 )->bool {
        if( c1 && c2 )
            return GetCardTypeString( c1->GetCardType() ) < GetCardTypeString( c2->GetCardType() );
        else
            return false;
    });

    int points = gold / 3;
    vector<SymbolsCounter> greenSymbols;
    for( auto & card : cards )
    {
        eCardType type = card->GetCardType();
        if( type == BLUE )
        {
            if( ArchitectureCard* blue = dynamic_cast<ArchitectureCard*>( card.get() ) )
                points += blue->GetPoints();
        }
        else if( type == RED )
        {
            if( MilitaryCard* red = dynamic_cast<MilitaryCard*>( card.get() ) )
                points += red->GetPoints();
        }
        else if( type == GREEN )
        {
            if( ScienceCard* green = dynamic_cast<ScienceCard*>( card.get() ) )
            {
                bool found = false;
                for( auto & s : greenSymbols )
                {
                    if( s.symbol == green->GetScienceSymbol() )
                    {
                        s.count++;
                        found = true;
                        break;
                    }
                }
                if( !found )
                    greenSymbols.push_back( SymbolsCounter( green->GetScienceSymbol() ) );
            }
        }
    }
    for( auto symbol : greenSymbols )
        points += (int)pow( symbol.count, 2 );

    return points;
}