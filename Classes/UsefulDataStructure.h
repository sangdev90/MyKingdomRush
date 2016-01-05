//
//  UsefulDataStructure.h
//  KingdomRush
//
//  Created by 贾佳菊 on 15/12/27.
//
//

#ifndef UsefulDataStructure_h
#define UsefulDataStructure_h

#include <stdio.h>

class BattleHeroInfoData{
public:
    //TODO:
};

class BattleTowerInfoData{
public:
    std::string name = "none";
    std::string attackTime = "none";
    std::string scope = "none";
};

class BattleMonsterInfoData{
public:
    std::string name = "none";
    int fullHP = 0;
    int currentHP = 0;
    int highAttack = 0;
    int lowAttack = 0;
    std::string defence = "none";
    int life = 0;
};

class BattleBossInfoData{
public:
    //TODO:
};

class BattlePowerInfoData{
public:
    std::string name = "none";
    std::string description = "none";
};

#endif /* UsefulDataStructure_h */
