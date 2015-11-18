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

class BattleLayer;

class Monster : public Person{
public:
    
    static Monster *createWithName(const std::string &name, const std::vector<cocos2d::Vec2> &path);
    
    Monster(const std::string &name):
    Person(name) {};
    
    virtual bool init() override;
    virtual void onEnter() override;
    virtual void onExit() override;
    
    virtual void run() override;
    virtual void attack(Person *attackTarget) override;
    virtual void die() override;
    virtual void update(float dt) override;
    
    void setPath(const std::vector<cocos2d::Vec2> &path){
        _pathVector = path;
    };
    
    void setBattleLayerPoint(BattleLayer *battleLayer){
        _battleLayerPointer = battleLayer;
    };
    
protected:
    MonsterData _myMonsterData;
    std::vector<cocos2d::Vec2> _pathVector;
    BattleLayer *_battleLayerPointer;
    cocos2d::Vec2 _currentRunTargetPoint;
    cocos2d::Vec2 _nextRunTargetPoint;
    std::string _faceTo;
    int _nextRunTargetPointIndex = 1;
    int _currentRunTargetPointIndex = 0;
    
    void _initMonsterData();
    void _initAnimationData();
    void _initBattleMapData();
    void _makeFaceTo();
};

#endif /* Monster_hpp */
