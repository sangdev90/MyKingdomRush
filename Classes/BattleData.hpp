//
//  BattleData.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/12.
//
//

#ifndef BattleData_hpp
#define BattleData_hpp

#include <stdio.h>
#include "cocos2d.h"

class BattleData {
public:
    
    int id;
    std::string battleName;
    
    std::vector<cocos2d::Vec2> defencePoint;
    std::vector<cocos2d::Vec2> towerBuildPoint;
    std::vector<cocos2d::Vec2> npcTowerBuildPoint;
    std::vector<std::string> monster;
    int coin;
    int hp;
};

#endif /* BattleData_hpp */
