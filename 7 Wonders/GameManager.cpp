#include "GameManager.h"
#include <fstream>
#include <algorithm>
#include "ProductionCard.h"
#include "MilitaryCard.h"
#include "ScienceCard.h"
#include "ArchitectureCard.h"
#include "GuildCard.h"
#include "IndustryCard.h"
#include "BonusCard.h"
#include "WonderCard.h"

GameManager GameManager::Game;

GameManager & GameManager::GetSingleton()
{
    return Game;
}

bool GameManager::LoadRecources()
{
    rapidxml::xml_document<> Doc;
	ifstream XmlFile{ strFileDirectory };
	if( !XmlFile.is_open() )
    {
		return false;
    }

    string content((std::istreambuf_iterator<char>(XmlFile)), std::istreambuf_iterator<char>());
	XmlFile.close();

	Doc.parse<0>( &content[0] );
    auto rootNode = Doc.first_node();
    rapidxml::xml_node<char> * tempNode = nullptr;

	if( !rootNode )
    {
		return false;
    }

    while( rootNode )
    {
        string key = rootNode->name();
        auto childNode = rootNode->first_node();
        if( key == "BROWN_CARDS" )
        {
            UploadProductionCards( childNode, eCardType::BROWN );
        }
        else if( key == "GREY_CARDS" )
        {
            UploadProductionCards( childNode, eCardType::GREY );
        }
        else if( key == "RED_CARDS" )
        {
            UploadMilitaryCards( childNode );
        }
        else if( key == "BLUE_CARDS" )
        {
            UploadArchitectureCards( childNode );
        }
        else if( key == "GREEN_CARDS" )
        {
            UploadScienceCards( childNode );
        }
        /*else if( key == "GOLD_CARDS" )
        {
            UploadGoldCards( childNode );
        }
        else if( key == "PURPLE_CARDS" )
        {
            UploadGuildCards( childNode );
        }
        else if( key == "WONDER_CARDS" )
        {
            UploadWonderCards( childNode );
        }*/
        rootNode = rootNode->next_sibling();
    }
    return true;
}

void GameManager::UploadProductionCards( rapidxml::xml_node<char> * node, eCardType type )
{
    if( !node )
        return;
    short int epoque = 0;
    Cost cost;
    eMaterial mat;
    int amount = 0;
    for( auto rootNode = node; rootNode; rootNode = rootNode->next_sibling() )
    {
        if( auto temp = rootNode->first_attribute( "EPOQUE" ) )
            epoque = atoi( temp->value() );
        auto childNode = rootNode->first_node();
        cost = UploadCost( childNode );
        if( childNode = childNode->next_sibling() )
        {            
            childNode = childNode->first_node();
            amount = atoi( childNode->value() );
            mat = GetMaterialFromString( childNode->first_attribute( "NAME" )->value() );
        }
        if( epoque == 1 )
            firstEpoqueCards.push_back( make_shared<ProductionCard>( type, epoque, cost, mat, amount ) );
        else if( epoque == 2 )
            secondEpoqueCards.push_back( make_shared<ProductionCard>( type, epoque, cost, mat, amount ) );
        else
            thirdEpoqueCards.push_back( make_shared<ProductionCard>( type, epoque, cost, mat, amount ) );
    }
}

Cost GameManager::UploadCost( rapidxml::xml_node<char> * node )
{    
    if( !node )
        return Cost{};
    string material;
    int amount;
    Cost cost;
    for( auto childNode = node->first_node(); childNode; childNode = childNode->next_sibling() )
    {
        if( auto temp = childNode->first_attribute( "NAME" ) )
            material = temp->value();
        else if( !strcmp( childNode->name(), "FREEBUILD" ) )
        {
            cost.freebuild = GetFreebuildFromString( childNode->value() );
            continue;
        }
        amount = atoi( childNode->value() );
        
        SingleCost sCost;
        sCost.amount = amount;
        sCost.material = GetMaterialFromString( material );
        cost.materials.push_back( sCost );
    }
    return cost;
}

void GameManager::UploadMilitaryCards( rapidxml::xml_node<char> * node )
{
    if( !node )
        return;
    short int epoque = 0;
    Cost cost;
    int strength = 0;
    for( auto rootNode = node; rootNode; rootNode = rootNode->next_sibling() )
    {
        if( auto temp = rootNode->first_attribute( "EPOQUE" ) )
            epoque = atoi( temp->value() );
        auto childNode = rootNode->first_node();
        cost = UploadCost( childNode );
        childNode = childNode->next_sibling();
        strength = atoi( childNode->value() );
        eFreebuild fb = EMPTY;
        if( auto tmp = rootNode->first_attribute( "FREEBUILD" ) )
            fb = GetFreebuildFromString( tmp->value() );
        if( epoque == 1 )
            firstEpoqueCards.push_back( make_shared<MilitaryCard>( RED, epoque, cost, strength, fb ) );
        else if( epoque == 2 )
            secondEpoqueCards.push_back( make_shared<MilitaryCard>( RED, epoque, cost, strength, fb ) ); 
        else
            thirdEpoqueCards.push_back( make_shared<MilitaryCard>( RED, epoque, cost, strength, fb ) );
    }
}

void GameManager::UploadScienceCards( rapidxml::xml_node<char> * node )
{
    if( !node )
        return;
    short int epoque = 0;
    Cost cost;
    eScienceSymbol symbol;
    for( auto rootNode = node; rootNode; rootNode = rootNode->next_sibling() )
    {
        if( auto temp = rootNode->first_attribute( "EPOQUE" ) )
            epoque = atoi( temp->value() );
        auto childNode = rootNode->first_node();
        cost = UploadCost( childNode );
        childNode = childNode->next_sibling();
        symbol = GetScienceSymbolFromString( childNode->value() );
        eFreebuild fb = EMPTY;
        if( auto tmp = rootNode->first_attribute( "FREEBUILD" ) )
            fb = GetFreebuildFromString( tmp->value() );

        if( epoque == 1 )
            firstEpoqueCards.push_back( make_shared<ScienceCard>( GREEN, epoque, cost, symbol, fb ) );
        else if( epoque == 2 )
            secondEpoqueCards.push_back( make_shared<ScienceCard>( GREEN, epoque, cost, symbol, fb ) );
        else
            thirdEpoqueCards.push_back( make_shared<ScienceCard>( GREEN, epoque, cost, symbol, fb ) ); 
    }
}

void GameManager::UploadArchitectureCards( rapidxml::xml_node<char> * node )
{
    if( !node )
        return;
    short int epoque = 0;
    Cost cost;
    int points;
    for( auto rootNode = node; rootNode; rootNode = rootNode->next_sibling() )
    {
        if( auto temp = rootNode->first_attribute( "EPOQUE" ) )
            epoque = atoi( temp->value() );
        auto childNode = rootNode->first_node();
        cost = UploadCost( childNode );
        childNode = childNode->next_sibling();
        points = atoi( childNode->value() );
        eFreebuild fb = EMPTY;
        if( auto tmp = rootNode->first_attribute( "FREEBUILD" ) )
            fb = GetFreebuildFromString( tmp->value() );

        if( epoque == 1 )
            firstEpoqueCards.push_back( make_shared<ArchitectureCard>( BLUE, epoque, cost, points, fb ) );
        else if( epoque == 2 )
            secondEpoqueCards.push_back( make_shared<ArchitectureCard>( BLUE, epoque, cost, points, fb ) );
        else
            thirdEpoqueCards.push_back( make_shared<ArchitectureCard>( BLUE, epoque, cost, points, fb ) );
    }
}

void GameManager::UploadGuildCards( rapidxml::xml_node<char> * node )
{
    if( !node )
        return;
    short int epoque = 0;
    Cost cost;
    int points = 0, gold = 0;
    for( auto rootNode = node; rootNode; rootNode = rootNode->next_sibling() )
    {
        if( auto temp = rootNode->first_attribute( "EPOQUE" ) )
            epoque = atoi( temp->value() );
        auto childNode = rootNode->first_node();
        cost = UploadCost( childNode );
        childNode = childNode->next_sibling();
        if( auto tmp = childNode->first_attribute( "POINTS" ) )
            points = atoi( tmp->value() );
        if( auto tmp = childNode->first_attribute( "GOLD" ) )
            gold = atoi( tmp->value() );
        vector<eCardType> types;
        for( auto cardTypeNode = childNode->first_node(); cardTypeNode; cardTypeNode = cardTypeNode->next_sibling() )
        {
            types.push_back( GetCardTypeFromString( cardTypeNode->value() ) );
        }
        //cards.push_back( make_shared<GuildCard>( PURPLE, epoque, cost, types, points, gold ) );
    }
}

void GameManager::UploadGoldCards( rapidxml::xml_node<char> * node )
{
    if( !node )
        return;
    short int epoque = 0;
    Cost cost;
    int points = 0, gold = 0;
    for( auto rootNode = node; rootNode; rootNode = rootNode->next_sibling() )
    {
        if( auto temp = rootNode->first_attribute( "EPOQUE" ) )
            epoque = atoi( temp->value() );
        auto childNode = rootNode->first_node();
        cost = UploadCost( childNode );
        childNode = childNode->next_sibling();
        eFreebuild fb = EMPTY;
        if( auto tmp = rootNode->first_attribute( "FREEBUILD" ) )
            fb = GetFreebuildFromString( tmp->value() );
        if( !strcmp( childNode->name(), "INDUSTRY" ) )
            UploadIndustryCards( childNode, epoque, cost );
        else
            UploadBonusCards( childNode, epoque, cost, fb );
    }
}

void GameManager::UploadIndustryCards( rapidxml::xml_node<char> * node, short int epoque, Cost cost )
{
    if( !node )
        return;
    eBonusType type;
    if( auto tmp = node->first_attribute( "TYPE") )
        type = GetBonusTypeFromString( tmp->value() );
    vector<eMaterial> materials;
    for( auto rootNode = node->first_node(); rootNode; rootNode = rootNode->next_sibling() )
    {
        materials.push_back( GetMaterialFromString( rootNode->value() ) );
    }

    if( epoque == 1 )
        firstEpoqueCards.push_back( make_shared<IndustryCard>( YELLOW, epoque, cost, materials, type ) );
    else if( epoque == 2 )
        secondEpoqueCards.push_back( make_shared<IndustryCard>( YELLOW, epoque, cost, materials, type ) );
    else
        thirdEpoqueCards.push_back( make_shared<IndustryCard>( YELLOW, epoque, cost, materials, type ) );
}

void GameManager::UploadBonusCards( rapidxml::xml_node<char> * node, short int epoque, Cost cost, eFreebuild free )
{
    if( !node )
        return;
    eCardType type = NONE;
    if( auto tmp = node->first_attribute( "TYPE") )
        type = GetCardTypeFromString( tmp->value() );
    int gold = 0, points = 0;
    if( auto tmp = node->first_attribute( "GOLD") )
        gold = atoi( tmp->value() );
    if( auto tmp = node->first_attribute( "POINTS") )
        points = atoi( tmp->value() );
    vector<eMaterial> materials;
    /*if( type == NONE )
        cards.push_back( make_shared<BonusCard>( YELLOW, epoque, cost, free, type, gold, points ) );
    else
        cards.push_back( make_shared<BonusCard>( YELLOW, epoque, cost, free, gold ) );*/
}

void GameManager::UploadWonderCards( rapidxml::xml_node<char> * node )
{
    if( !node )
        return;
    Cost cost;
    for( auto rootNode = node; rootNode; rootNode = rootNode->next_sibling() )
    {
        auto childNode = rootNode->first_node();
        cost = UploadCost( childNode );
        childNode = childNode->next_sibling();
        int gold = 0, points = 0, military = 0;
        vector<eMaterial> materials;
        vector<eBonusType> bonuses;
        if( childNode && !strcmp( childNode->name(), "GOLD" ) )
        {
            gold = atoi( childNode->value() );
            childNode = childNode->next_sibling();
        }
        if( childNode && !strcmp( childNode->name(), "POINTS" ) )
        {
            points = atoi( childNode->value() );
            childNode = childNode->next_sibling();
        }
        if( childNode && !strcmp( childNode->name(), "MILITARY" ) )
        {
            military = atoi( childNode->value() );
            childNode = childNode->next_sibling();
        }
        if( childNode && !strcmp( childNode->name(), "BONUSES" ) )
        {   
            for( auto bonusNode = childNode->first_node(); bonusNode; bonusNode = bonusNode->next_sibling() )
            {
                bonuses.push_back( GetBonusTypeFromString( bonusNode->value() ) );
            }
            childNode = childNode->next_sibling();
        }
        if( childNode && !strcmp( childNode->name(), "PRODUCTION" ) )
        {
            for( auto materialNode = childNode->first_node(); materialNode; materialNode = materialNode->next_sibling() )
            {
                materials.push_back( GetMaterialFromString( materialNode->value() ) );
            }
        }
        //cards.push_back( make_shared<WonderCard>( WONDER, cost, points, gold, military, bonuses, materials ) );
    }
}

void GameManager::DisplayCards( vector<CardPtr> cards )const
{
    int i = 1;
    for( CardPtr c : cards )
    {
        if( c )
        {
            cout << i << ")\n";
            c->DisplayCard();
            cout << endl;
            i++;
        }
    }
}

vector<CardPtr> GameManager::DrawCardSet()
{
    vector<CardPtr> currentSet(5);
    if( epoque == 1 && firstEpoqueCards.size() )
    {
        std::copy( firstEpoqueCards.begin(), firstEpoqueCards.begin() + 5, currentSet.begin() );
        firstEpoqueCards.erase( firstEpoqueCards.begin(), firstEpoqueCards.begin() + 5 );
    }
    else if( epoque == 2 && secondEpoqueCards.size() )
    {
        std::copy( secondEpoqueCards.begin(), secondEpoqueCards.begin() + 5, currentSet.begin() );
        secondEpoqueCards.erase( secondEpoqueCards.begin(), secondEpoqueCards.begin() + 5 );
    }
    else if( thirdEpoqueCards.size() )
    {
        std::copy( thirdEpoqueCards.begin(), thirdEpoqueCards.begin() + 5, currentSet.begin() );
        thirdEpoqueCards.erase( thirdEpoqueCards.begin(), thirdEpoqueCards.begin() + 5 );
    }
    return currentSet;
}

void GameManager::DrawCard( vector<CardPtr> & currentSet )
{
    if( currentSet.size() == 0 )
        return;
    if( epoque == 1 && firstEpoqueCards.size() )
    {
        currentSet.push_back( firstEpoqueCards[0] );
        firstEpoqueCards.erase( firstEpoqueCards.begin() );
    }
    else if( epoque == 2 && secondEpoqueCards.size() )
    {
        currentSet.push_back( secondEpoqueCards[0] );
        secondEpoqueCards.erase( secondEpoqueCards.begin() );
    }
    else if( epoque == 3 && thirdEpoqueCards.size() )
    {
        currentSet.push_back( thirdEpoqueCards[0] );
        thirdEpoqueCards.erase( thirdEpoqueCards.begin() );
    }
}

void GameManager::StartGame()
{
    std::random_shuffle( firstEpoqueCards.begin(), firstEpoqueCards.end() );
    std::random_shuffle( secondEpoqueCards.begin(), secondEpoqueCards.end() );
    std::random_shuffle( thirdEpoqueCards.begin(), thirdEpoqueCards.end() );

    bool run = true;
    Player p1 = Player( "Player 1" ), p2 = Player( "Player 2" );
    firstPlayer = make_shared<Player>( p1 );
    secondPlayer = make_shared<Player>( p2 );
    activePlayer = firstPlayer;
    vector<CardPtr> currentSet = DrawCardSet();
    string choice;

    while( run )
    {
        if( currentSet.empty() )
        {
            epoque++;
            if( epoque > 3 )
                break;
            currentSet = DrawCardSet();
        }
        cout << "\n\n\n*******************************************************************************\nEPOQUE " << epoque << "\n";
        cout << activePlayer->GetName() + ": Pick a card.\t\t\t\tGOLD: " << activePlayer->GetGold() << "\n\n";
        activePlayer->DisplayCards();
        DisplayCards( currentSet );
        cin >> choice;
        int result = InterpretChoice( choice );
        if( result == 0 )
            return;

        else if( result < 0 )
        {
            cout << "\nInvalid choice. Press Enter to continue.\n\n";
            cin.sync();
            getchar();
            continue;
        }
        cout << "\nDo you want to sell this card for " << CARD_PRICE << " coins? (Press Y for YES or N for NO)\n";
        cin >> choice;
        if( choice == "y" )
            SellCard( result - 1, currentSet );
        else if( choice != "n" )
        {
            cout << "\nInvalid choice. Press Enter to continue.\n\n";
            cin.sync();
            getchar();
            continue;
        }
        else
        {
            result = CollectCard( result - 1, currentSet );
            if( result )
            {
                cout << "\nCard collected. Press Enter to continue.\n\n";
                cin.sync();
                getchar();
            }
            else
            {
                cout << "\nYou can't afford the card. Press Enter to continue.\n\n";
                cin.sync();
                getchar();
                continue;
            }
        }
        cout << "Points: " << activePlayer->GetTotalPoints();
        activePlayer = activePlayer == firstPlayer ? secondPlayer : firstPlayer;
    }
    activePlayer = firstPlayer->GetTotalPoints() > secondPlayer->GetTotalPoints() ? firstPlayer : secondPlayer;
    cout << "\n\t\t\t\tGAME OVER\n\nThe winner is " << activePlayer->GetName();
    cin.sync();
    getchar();
}

int GameManager::InterpretChoice( const string choice )
{
    if( choice >= "1" && choice <= "5" )
        return atoi( choice.c_str() );
    if( choice[0] == 27 )
        return 0;
    else
        return -1;
}

void GameManager::SellCard( int card, vector<CardPtr> & currentSet )
{
    if( currentSet.empty() || currentSet.size() < unsigned(card + 1) )
        return;
    usedCards.push_back( currentSet[card] );
    currentSet.erase( currentSet.begin() + card );
    activePlayer->AddGold( CARD_PRICE );
    DrawCard( currentSet );
}

bool GameManager::CollectCard( int card, vector<CardPtr> & currentSet )
{
    if( currentSet.empty() || currentSet.size() < unsigned(card + 1) )
        return false;
    if( activePlayer->CheckIfAfordable( currentSet[card]->GetCost() ) )
    {
        activePlayer->CollectCard( currentSet[card] );
        usedCards.push_back( currentSet[card] );
        currentSet.erase( currentSet.begin() + card );
        DrawCard( currentSet );
        return true;
    }
    else
        return false;
}