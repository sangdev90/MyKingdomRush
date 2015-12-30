//
//  MonsterActor.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/29.
//
//

#ifndef MonsterActor_hpp
#define MonsterActor_hpp

#include <stdio.h>
#include "cocos2d.h"

#include "PersonActor.hpp"

class MonsterActor : public PersonActor{
public:
    static MonsterActor *createMonsterActorByName(const std::string &name, const PersonActorAnimatoinData &animationData);
    
    MonsterActor(const std::string &name):
    PersonActor(name) {};
    
protected:
    
};

#endif /* MonsterActor_hpp */
