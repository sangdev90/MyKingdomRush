//
//  Archer.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/25.
//
//

#include "Archer.hpp"
#include "ToolFunction.hpp"
#include "GameData.hpp"

USING_NS_CC;

Archer *Archer::createArcher(){

    Archer *newArcher = new (std::nothrow) Archer();
    if (newArcher && newArcher->initArcher()){
        newArcher->autorelease();
        return newArcher;
    }
    
    delete newArcher;
    newArcher = nullptr;
    return nullptr;
    
}

bool Archer::initArcher(){
    if (!this->initWithSpriteFrameName(getTowerShooterSpriteFrameNameByNameAndLevel(_name, _level))){
        return false;
    }
    
    return true;
}

void Archer::attack(const cocos2d::Vec2 &from, const cocos2d::Vec2 &to, const std::function<void ()> &attackCallback){
    
}

void Archer::updateTowerShooterLevel(const std::string &level){
    TowerShooter::updateTowerShooterLevel(level);
    
}


