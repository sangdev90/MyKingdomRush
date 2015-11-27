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
    this->addChild(_towerActor, 1);
    
    return true;
    
}

void ArcherTower::updateLevel(){
    Tower::updateLevel();
}