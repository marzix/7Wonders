#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_
#include <iostream>
#include <string>

using namespace std;
const int CARD_PRICE = 3;

const string strFileDirectory   = "../Cards.xml";
const string filename           = "../train.txt";

const string strCardTypeBrown     = "Brown";
const string strCardTypeGrey      = "Grey";
const string strCardTypeRed       = "Red";
const string strCardTypeGreen     = "Green";
const string strCardTypeGold      = "Gold";
const string strCardTypeBlue      = "Blue";
const string strCardTypePurple    = "Purple";
const string strCardTypeWonder    = "Wonder";

const string strMaterialWood      = "Wood";
const string strMaterialBrick     = "Brick";
const string strMaterialStone     = "Stone";
const string strMaterialGlass     = "Glass";
const string strMaterialPapyrus   = "Papyrus";
const string strMaterialGold      = "Gold";

const string strFreebuildHorseshoe= "Horseshoe";
const string strFreebuildSword    = "Sword";
const string strFreebuildBook     = "Book";
const string strFreebuildGearwheel= "Gearwheel";
const string strFreebuildMask     = "Mask";
const string strFreebuildMoon     = "Moon";
const string strFreebuildDrop     = "Drop";
const string strFreebuildTower    = "Tower";
const string strFreebuildVase     = "Vase";
const string strFreebuildBarrel   = "Barrel";
const string strFreebuildTemple   = "Temple";
const string strFreebuildSun      = "Sun";
const string strFreebuildPillar   = "Pillar";
const string strFreebuildHarph    = "Harph";
const string strFreebuildPot      = "Pot";
const string strFreebuildTarget   = "Target";
const string strFreebuildArmor    = "Armor";

const string strSymbolMedicine    = "Medicine";
const string strSymbolAstronomy   = "Astronomy";
const string strSymbolEngineering = "Engineering";

const string strBonusTypeLowerCost    = "Lower cost";
const string strBonusTypeProducton    = "Production";
const string strBonusTypeSecondTurn   = "Second turn";
const string strBonusTypeTakeCoins    = "Take coins";
const string strBonusTypeTakeGreyCard = "Take grey card";
const string strBonusTypeTakeBrownCard= "Take brown card";

//Card types
enum eCardType {
    
    BROWN,
    GREY,
    RED,
    GREEN,
    YELLOW,
    BLUE,
    PURPLE,
    WONDER,
    NONE
};

enum eMaterial {

    BRICK,
    STONE,
    WOOD,
    GLASS,
    PAPYRUS,
    GOLD
};

enum eFreebuild {

    HORSESHOE,
    SWORD,
    BOOK,
    GEARWHEEL,
    MASK,
    MOON,
    DROP,
    TOWER,
    VASE,
    BARREL,
    TEMPLE,
    SUN,
    PILLAR,
    HARPH,
    POT,
    TARGET,
    ARMOR,
    EMPTY
};

enum eScienceSymbol {

    MEDICINE,
    ASTRONOMY,
    ENGINEERING
};

enum eBonusType {

    LOWER_COST,
    PRODUCTION,
    SECOND_TURN,
    TAKE_COINS,
    TAKE_GREY_CARD,
    TAKE_BROWN_CARD
};

const string GetCardTypeString( eCardType type );
eCardType GetCardTypeFromString( string name );
const string GetMaterialString( eMaterial type );
eMaterial GetMaterialFromString( string name );
const string GetFreebuildString( eFreebuild type );
eFreebuild GetFreebuildFromString( string name );
const string GetScienceSymbolString( eScienceSymbol type );
eScienceSymbol GetScienceSymbolFromString( string name );
const string GetBonusTypeString( eBonusType type );
eBonusType GetBonusTypeFromString( string name );

#endif