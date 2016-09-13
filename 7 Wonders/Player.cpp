#include "Player.h"
#include "MilitaryCard.h"
#include "ArchitectureCard.h"
#include "ProductionCard.h"
#include "ScienceCard.h"
#include <algorithm>
#include <sstream>

Player::Player( string _name, char* type )
: name( _name )
{
    if( strcmp( type, "h" ) == 0 )
        playerType = HUMAN;
    else
        playerType = AI;
}

void Player::SetPlayerType( ePlayerType type )
{
    playerType = type;
}

string Player::GetName()const
{
    return name;
}

int Player::GetGold()const
{
    return gold;
}

ePlayerType Player::GetPlayerType()const
{
    return playerType;
}

void Player::CollectCard( CardPtr card, Cost costLeft )
{
    for( SingleCost sc : costLeft.materials )
    {
        if( sc.material == GOLD && sc.amount < gold )
            gold -= sc.amount;
    }
    cards.push_back( card );

	if (card->GetCardType() == BROWN || card->GetCardType() == GREY) 
	{
		ProductionCard * browngrey = dynamic_cast<ProductionCard*>(card.get());
		ownedMaterials.push_back(browngrey->GetProducedMaterial());
	}
}

void Player::AddGold( int g )
{
    gold += g;
}

bool Player::CheckIfAfordable( Cost & cardCost )
{
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
    int goldCost = 0;
    if( cardCost.materials.empty() )
        return true;
    else
    {
        for( unsigned int i = 0; i < cardCost.materials.size(); i++ )
        {
            if( cardCost.materials[i].material != GOLD )
            {
                if( cardCost.materials[i].material == PAPYRUS || cardCost.materials[i].material == GLASS )
                    goldCost += cardCost.materials[i].amount * 3;
                else
                    goldCost += cardCost.materials[i].amount * 2;
            }
            else
                goldCost += cardCost.materials[i].amount;
            cardCost.materials.erase( cardCost.materials.begin() + i );
        }
        if( goldCost <= gold )
        {
            SingleCost sc;
            sc.amount = goldCost;
            sc.material = GOLD;
            cardCost.materials.push_back( sc );
            return true;
        }
        else
            return false;
    }
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

int Player::GetScienceCardSymbolCount( eScienceSymbol symbol )const
{
    int symbolCounter = 0;
    for( auto & card : cards )
    {
        eCardType type = card->GetCardType();
        if( type == GREEN )
        {
            if( ScienceCard* green = dynamic_cast<ScienceCard*>( card.get() ) )
            {
                if( green->GetScienceSymbol() == symbol )
                    symbolCounter++;
            }
        }
    }
    return symbolCounter;
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
    //zielone: liczba kart o danym symbolu do kwadratu
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

int Player::GetMilitaryStrength()
{
    int points = 0;

    for( auto & card : cards )
    {
        if( card && card->GetCardType() == RED )
        {
            if( MilitaryCard* red = dynamic_cast<MilitaryCard*>( card.get() ) )
                points += red->GetPoints();
        }
    }
    return points;
}

string Player::SaveTurn( int epoque, vector<CardPtr> cards )
{
	string currentTurn = GetCurrentTurn(epoque, cards);
    courseOfGameText += currentTurn;

    return currentTurn;
}

vector<SingleCost> Player::GetOwnedMaterials()
{
	return ownedMaterials;
}

string Player::GetCurrentTurn(int epoque, vector<CardPtr> cards)
{
	char buffer[10];
	string currentTurn = "";
	_itoa_s(epoque, buffer, 10);
	currentTurn += buffer;

	std::ostringstream strs;
	double cardCode;
	double cardValue;
	MilitaryCard * red;
	ArchitectureCard * blue;
	ProductionCard * browngrey;
    ScienceCard * green;
	double cost = 0.0;
	int amount = 0;

	for (auto card : cards)
	{
        auto cardCost = card->GetCost();
        cardCode = (double)(atoi(card->GetCardCode().c_str()));
		if( CheckIfAfordable( cardCost ) )
		{
			/*
			for (SingleCost material : card->GetCost().materials)
			{
				amount = material.amount;
				for (SingleCost owned : this->ownedMaterials)
				{
					if (material.material == owned.material) {
						amount -= owned.amount;
					}
				}
				if (amount < 0)
					amount = 0;*/
            if( cardCost.materials.size() && cardCost.materials[0].material == GOLD )
				cost += cardCost.materials[0].amount / 3;

			if ( cardCode == 1.0 )
			{
				browngrey = dynamic_cast<ProductionCard*>(card.get());
				cardValue = browngrey->GetProducedMaterial().amount * 2 - cost;
			}
			else if (cardCode == 2.0)
			{
				browngrey = dynamic_cast<ProductionCard*>(card.get());
				cardValue = browngrey->GetProducedMaterial().amount * 2 - cost;
			}
			else if (cardCode == 3.0)
			{
				red = dynamic_cast<MilitaryCard*>(card.get());
				cardValue = red->GetPoints() - cost;
			}
			else if (cardCode == 4.0)
			{
                cardValue = 0.0;
                if( green = dynamic_cast<ScienceCard*>( card.get() ) )
                {
                    int symbolCount = GetScienceCardSymbolCount( green->GetScienceSymbol() );
                    cardValue = pow( (symbolCount + 1), 2 ) - pow( symbolCount, 2 ) - cost;
                }
			}
			else if (cardCode == 5.0)
			{
				blue = dynamic_cast<ArchitectureCard*>(card.get());
				cardValue = blue->GetPoints() - cost;
			}
			cost = 0.0;
            
            //warunek, który nigdy nie wyst¹pi, ale dla pewnoœci mo¿e zostaæ
			if (cardValue < 0.0)
				strs << -1;
			else
				strs << cardCode + (double)( (this->GetTotalPoints() + cardValue) / 100.0 );
		}
		else
            strs << cardCode + (double)( (this->GetTotalPoints() + CARD_PRICE / 3.0) / 100.0 );

        currentTurn += " " + strs.str();
        strs.str("");
        strs.clear();
        cardCode = cardValue = 0.0;
	}
	for (int i = cards.size(); i < 5; i++)
	{
		currentTurn += " 0";
	}
	/*_itoa_s( GetTotalPoints(), buffer, 10 );
	currentTurn += " ";
	currentTurn += buffer;*/
	currentTurn += "\n\n";
	return currentTurn;
}

void Player::SaveTurn( unsigned choice )
{
    for( unsigned i = 0; i < 5; i++ )
    {
        if( i == choice )
            courseOfGameText += "1 ";
        else
            courseOfGameText += "0 ";
    }
    courseOfGameText += "\n\n";
}

string Player::GetCourseOfGame()const
{
    return courseOfGameText;
}