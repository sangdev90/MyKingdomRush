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
    cocos2d::Vec2 monsterAppearPoint;
    cocos2d::Vec2 defencePoint;
    std::vector<cocos2d::Vec2> towerBuildPoint;
    int coin;
    int hp;
};

#endif /* BattleData_hpp */
