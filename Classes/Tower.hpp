//
//  Tower.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/21.
//
//

#ifndef Tower_hpp
#define Tower_hpp

#include <stdio.h>
#include "cocos2d.h"

#include "ToolFunction.hpp"
#include "ResourcesPath.h"
#include "GameData.hpp"
#include "TowerData.hpp"

class BattleLayer;
class TowerActor;
class Monster;

class AttackScopeData {
public:
    int longAxis;
    int shortAxis;
};

class Tower : public cocos2d::Sprite{
public:
    
    static Tower *createTowerByName(const std::string &name, BattleLayer *battleLayer);
    
    Tower(const std::string &name):
    _name(name), _level("level1") {};
    virtual ~Tower() = 0;
    
#pragma mark - Member Method
    
    void changeLevel(const std::string &levelTag = "");
    void updateTowerData();
    void setBattleLayerPointer(BattleLayer *battleLayer){
        _battleLayerPointer = battleLayer;
    };
    void initAttackScopeData(){
        std::string scopeDescription = GameData::getInstance()->getTowerDataByTowerNameAndLevel(_name, _level).scope;
        // short, average, long
        if (scopeDescription == "short"){
            _attackScopeData.longAxis = 250;
            _attackScopeData.shortAxis = 150;
        }else if (scopeDescription == "average"){
            _attackScopeData.longAxis = 320;
            _attackScopeData.shortAxis = 180;
        }else if (scopeDescription == "long"){
            _attackScopeData.longAxis = 400;
            _attackScopeData.shortAxis = 200;
        }else {
            CCLOG("我不认识这个塔的攻击范围描述：%s，那我就认为是 0 吧！", scopeDescription.c_str());
            _attackScopeData.longAxis = 0;
            _attackScopeData.shortAxis = 0;
        }
    }
    bool isMonsterCanAttack(Monster *monster);
    
#pragma mark - Impure Virtual Method
    
    virtual void updateLevel();
    virtual bool initTower();
    virtual Monster *findAttackTarget();
    virtual void onEnter();
    virtual void onExit();
    
#pragma mark - Pure Virtual Method
    
    virtual void attack(const cocos2d::Vec2 &from, const cocos2d::Vec2 &to, const std::function<void ()> &attackCallback) = 0;
    
protected:
    
    BattleLayer *_battleLayerPointer;
    
    std::string _name;
    std::string _level = "level1";
    std::string _info;
    
    TowerActor *_towerActor;
    
    Monster *_attackTarget;
    AttackScopeData _attackScopeData;
    enum {
//        StandState = 0, //塔除了找人就是打人，要静立的状态没用
        FindState = 0,
        AttackState,
        MisfireState
    };
    int _towerState = FindState;
};


#endif /* Tower_hpp */
