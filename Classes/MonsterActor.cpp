//
//  MonsterActor.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/29.
//
//

#include "MonsterActor.hpp"

MonsterActor *MonsterActor::createMonsterActorByName(const std::string &name, const PersonActorAnimatoinData &animationData){
    MonsterActor *monsterActor = new (std::nothrow) MonsterActor(name);
    if (monsterActor && monsterActor->initWithAnimationData(animationData)){
        monsterActor->autorelease();
        return monsterActor;
    }
    
    delete monsterActor;
    monsterActor = nullptr;
    return nullptr;
    
}
