//
//  Monster.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/14.
//
//

#ifndef Monster_hpp
#define Monster_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Person.hpp"
#include "MonsterData.hpp"

class Monster : public Person{
public:
    
    static Monster *createWithName(const std::string &name);
    
    Monster(const std::string &name):
    Person(name) {};
    
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;
    
    virtual void run() override;
    virtual void attack(Person *attackTarget) override;
    virtual void die() override;
    
    void initMonsterData();
    void initAnimationData();
    
private:
    MonsterData myMonsterData;
    
};

#endif /* Monster_hpp */
