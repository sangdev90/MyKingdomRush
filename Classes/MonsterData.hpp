//
//  MonsterData.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/14.
//
//

#ifndef MonsterData_hpp
#define MonsterData_hpp

#include <stdio.h>
#include "cocos2d.h"

class MonsterData {
public:
    
    int id;
    std::string name;
    
    int highPhysicalAttack;
    int lowPhysicalAttack;
    int highMagicAttack;
    int lowMagicAttack;
    int remotePhysicalAttack;
    int remoteMagicAttack;
    std::string physicalDefence;
    std::string magicDefence;
    int healthPoint;
    std::string speed;
    bool canAttack;
    std::string attackState;
    std::string bullet;
    int attackRange;
    int remoteAttackRange;
    std::string afterlife;
    int life;
    int bounty;
    
    int runTowardFrameNumber;
    int runForwardFrameNumber;
    int runBackwardFrameNumber;
    int dieFrameNumber;
    int attackFrameNumber;
    int attackRemoteFrameNumber;
    int releaseSkillFrameNumber;
};

#endif /* MonsterData_hpp */
