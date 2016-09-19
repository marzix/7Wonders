#include "Constants.h"

const string GetCardTypeString( eCardType type )
{
    switch( type )
    {
    case BROWN:     return strCardTypeBrown; 
    case GREY:      return strCardTypeGrey;  
    case RED:       return strCardTypeRed;   
    case GREEN:     return strCardTypeGreen; 
    case YELLOW:    return strCardTypeGold;  
    case BLUE:      return strCardTypeBlue;  
    case PURPLE:    return strCardTypePurple;
    case WONDER:    return strCardTypeWonder;
    case NONE:
    default:        return "None";
    }
}


const string GetMaterialString( eMaterial type )
{
    switch( type )
    {
    case BRICK:     return strMaterialBrick;
    case STONE:     return strMaterialStone;
    case WOOD:      return strMaterialWood;
    case GLASS:     return strMaterialGlass;
    case PAPYRUS:   return strMaterialPapyrus;
    case GOLD:
    default:        return strMaterialGold;
    }
}

const string GetFreebuildString( eFreebuild type )
{
    switch( type )
    {
    case HORSESHOE: return strFreebuildHorseshoe; 
    case SWORD:     return strFreebuildSword;
    case BOOK:      return strFreebuildBook;
    case GEARWHEEL: return strFreebuildGearwheel;
    case MASK:      return strFreebuildMask;
    case MOON:      return strFreebuildMoon;
    case DROP:      return strFreebuildDrop;
    case TOWER:     return strFreebuildTower;
    case VASE:      return strFreebuildVase;
    case BARREL:    return strFreebuildBarrel;
    case TEMPLE:    return strFreebuildTemple;
    case SUN:       return strFreebuildSun;
    case PILLAR:    return strFreebuildPillar;
    case HARPH:     return strFreebuildHarph;
    case POT:       return strFreebuildPot;
    case TARGET:    return strFreebuildTarget;
    case ARMOR:     return strFreebuildArmor;
    default:        return "Empty";
    }
}

const string GetScienceSymbolString( eScienceSymbol type )
{
    switch( type )
    {
    case MEDICINE:      return strSymbolMedicine;
    case ASTRONOMY:     return strSymbolAstronomy;
    case ENGINEERING:
    default:            return strSymbolEngineering;
    }
}

const string GetBonusTypeString( eBonusType type )
{
    switch( type )
    {
    case LOWER_COST:        return strBonusTypeLowerCost;
    case PRODUCTION:        return strBonusTypeProducton;
    case SECOND_TURN:       return strBonusTypeSecondTurn;
    case TAKE_COINS:        return strBonusTypeTakeCoins;
    case TAKE_GREY_CARD:    return strBonusTypeTakeGreyCard;
    case TAKE_BROWN_CARD:
    default:                return strBonusTypeTakeBrownCard;
    }
}

eCardType GetCardTypeFromString( string name )
{
    if( name == strCardTypeBlue )
        return BLUE;
    else if( name == strCardTypeBrown )
        return BROWN;
    else if( name == strCardTypeGold )
        return YELLOW;
    else if( name == strCardTypeGreen )
        return GREEN;
    else if( name == strCardTypeGrey )
        return GREY;
    else if( name == strCardTypePurple )
        return PURPLE;
    else if( name == strCardTypeRed )
        return RED;
    else
        return WONDER;
}

eMaterial GetMaterialFromString( string name )
{
    if( name == strMaterialBrick )
        return BRICK;
    else if( name == strMaterialGlass )
        return GLASS;
    else if( name == strMaterialGold )
        return GOLD;
    else if( name == strMaterialPapyrus )
        return PAPYRUS;
    else if( name == strMaterialStone )
        return STONE;
    else
        return WOOD;
}

eFreebuild GetFreebuildFromString( string name )
{
    if( name == strFreebuildArmor )
        return ARMOR;
    else if( name == strFreebuildBarrel )
        return BARREL;
    else if( name == strFreebuildBook )
        return BOOK;
    else if( name == strFreebuildDrop )
        return DROP;
    else if( name == strFreebuildGearwheel )
        return GEARWHEEL;
    else if( name == strFreebuildHarph )
        return HARPH;
    else if( name == strFreebuildHorseshoe )
        return HORSESHOE;
    else if( name == strFreebuildMask )
        return MASK;
    else if( name == strFreebuildMoon )
        return MOON;
    else if( name == strFreebuildPillar )
        return PILLAR;
    else if( name == strFreebuildPot )
        return POT;
    else if( name == strFreebuildSun )
        return SUN;
    else if( name == strFreebuildSword )
        return SWORD;
    else if( name == strFreebuildTarget )
        return TARGET;
    else if( name == strFreebuildTemple )
        return TEMPLE;
    else if( name == strFreebuildTower )
        return TOWER;
    else
        return VASE;    
}

eScienceSymbol GetScienceSymbolFromString( string name )
{
    if( name == strSymbolAstronomy )
        return ASTRONOMY;
    else if( name == strSymbolEngineering )
        return ENGINEERING;
    else
        return MEDICINE;
}

eBonusType GetBonusTypeFromString( string name )
{
    if( name == strBonusTypeLowerCost )
        return LOWER_COST;
    else if( name == strBonusTypeProducton )
        return PRODUCTION;
    else if( name == strBonusTypeSecondTurn )
        return SECOND_TURN;
    else if( name == strBonusTypeTakeBrownCard )
        return TAKE_BROWN_CARD;
    else if( name == strBonusTypeTakeCoins )
        return TAKE_COINS;
    else
        return TAKE_GREY_CARD;
}