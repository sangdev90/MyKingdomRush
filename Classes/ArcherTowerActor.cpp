//
//  ArcherTowerActor.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/25.
//
//

#include "ArcherTowerActor.hpp"
#include "ToolFunction.hpp"
#include "TowerShooter.hpp"
USING_NS_CC;

ArcherTowerActor *ArcherTowerActor::createArcherTowerActor(){
    
    ArcherTowerActor *newArcherTowerActor = new (std::nothrow) ArcherTowerActor();
    if (newArcherTowerActor && newArcherTowerActor->initArcherTowerActor()){
        newArcherTowerActor->autorelease();
        return newArcherTowerActor;
    }
    
    delete newArcherTowerActor;
    newArcherTowerActor = nullptr;
    return nullptr;
    
}

bool ArcherTowerActor::initArcherTowerActor(){
    if (!this->initWithSpriteFrameName(getTowerSriteFrameNameByNameAndLevel(_name, "level1"))){
        return false;
    }
    
    _leftTowerShooter = TowerShooter::createTowerShooterByName(GameData::getInstance()->getTowerActorDataByNameAndLevel(_name, _level).shooterName);
    _rightTowerShooter = TowerShooter::createTowerShooterByName(GameData::getInstance()->getTowerActorDataByNameAndLevel(_name, _level).shooterName);
    _leftTowerShooter->setPosition(90, 110);
    _rightTowerShooter->setPosition(120, 110);
    this->addChild(_leftTowerShooter, 1);
    this->addChild(_rightTowerShooter, 1);
    
    return true;
}

void ArcherTowerActor::attack(const cocos2d::Vec2 &from, const cocos2d::Vec2 &to, const std::function<void ()> &attackCallback){
    //TODO: 这里处理 TowerShooter 的 attack
}

void ArcherTowerActor::updateTowerLevel(const std::string &level){
    TowerActor::updateTowerLevel(level);
    
    //TODO: 这里处理 TowerShooter 的 update
    
}