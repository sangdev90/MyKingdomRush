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
    
    int numberOfAttackFrame;
    int numberOfDieFrame;
    int numberOfForwardFrame;
    int numberOfTowardFrame;
    int numberOfBcakwardFrame;
    
    int hp;
    int speed;
};

#endif /* MonsterData_hpp */
