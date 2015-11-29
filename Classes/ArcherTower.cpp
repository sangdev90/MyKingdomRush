//
//  ArcherTower.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/27.
//
//

#include "ArcherTower.hpp"
#include "ToolFunction.hpp"
#include "GameData.hpp"
#include "TowerActor.hpp"
#include "Monster.hpp"
#include "BattleLayer.hpp"

USING_NS_CC;

ArcherTower *ArcherTower::createArcherTower(){
    
    ArcherTower *newArcherTower = new (std::nothrow) ArcherTower();
    if (newArcherTower && newArcherTower->initTower()){
        newArcherTower->autorelease();
        return newArcherTower;
    }
    
    delete newArcherTower;
    newArcherTower = nullptr;
    return nullptr;
    
}

bool ArcherTower::initTower(){
    
    if (!Tower::initTower()){
        return false;
    }
    
    _towerActor = TowerActor::createTowerActorByName(_name);
//    _towerActor->setAnchorPoint(Vec2(0.5, 0));
//    _towerActor->setPosition(0, 0);
    this->addChild(_towerActor, 1);
    
    return true;
    
}

void ArcherTower::onEnter(){
    Tower::onEnter();
//    this->scheduleUpdate();
}

void ArcherTower::onExit(){
    Tower::onExit();
    this->unscheduleUpdate();
}

void ArcherTower::updateLevel(){
    Tower::updateLevel();
}

void ArcherTower::attack(const cocos2d::Vec2 &from, const cocos2d::Vec2 &to, const std::function<void ()> &attackCallback){
    _towerActor->attack(from, to, attackCallback);
}

void ArcherTower::update(float dt){
    
    if (_towerState == MisfireState){
        return;
    }
    
    if (_towerState == FindState){
        _attackTarget = this->findAttackTarget();
        if (_attackTarget){
            _towerState = AttackState;
        }
    }
    
    if (_towerState == AttackState){
        if (_attackTarget == nullptr){
            CCLOG("攻击目标还是空的，没拦住！");
            return;
        }
        if (_attackTarget->isDie){
            _towerState = FindState;
            return;
        }else {
            Vec2 nodePointOnMap = _attackTarget->getPosition();
            Vec2 worldPoint = _battleLayerPointer->getSomethingOnMapWorldPoint(_attackTarget);
            Vec2 nodeMonsterPosition = this->convertToNodeSpaceAR(worldPoint);
            CCLOG("这次坐标转换应该对了吧！");
            CCLOG("(%f, %f), (%f, %f), (%f, %f)", nodePointOnMap.x, nodePointOnMap.y, worldPoint.x, worldPoint.y, nodeMonsterPosition.x, nodeMonsterPosition.y);
            
//            this->attack(<#const cocos2d::Vec2 &from#>, <#const cocos2d::Vec2 &to#>, <#const std::function<void ()> &attackCallback#>)
        }
    }
}

