//
//  Tower.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/21.
//
//

#include "Tower.hpp"
#include "GameData.hpp"

#include "ArcherTower.hpp"
#include "DefenceTower.hpp"
#include "MageTower.hpp"
#include "ArtilleryTower.hpp"

USING_NS_CC;

Tower *Tower::createTowerByName(const std::string &name, BattleLayer *battleLayer){
    
    if (name == GameData::getInstance()->towerName.archerTower){
        Tower *archerTower = ArcherTower::createArcherTower();
        archerTower->setBattleLayerPointer(battleLayer);
        return archerTower;
    }
    
    if (name == GameData::getInstance()->towerName.defenceTower){
        
    }
    
    if (name == GameData::getInstance()->towerName.mageTower){
        
    }
    
    if (name == GameData::getInstance()->towerName.artilleryTower){
        
    }
    
    CCLOG("要创建一个不知名的 Tower : %s ", name.c_str());
    return nullptr;
    
}

void Tower::changeLevel(const std::string &levelTag){
    
    if (_level == "level1"){
        _level = "level2";
        this->updateTowerData();
        return;
    }else if (_level == "level2"){
        _level = "level3";
        this->updateTowerData();
        return;
    }else{
        if (levelTag == "level41" || levelTag == "level42"){
            _level = levelTag;
            this->updateTowerData();
            return;
        }else {
            CCLOG("I Don't Know Chang My Level To What!!!!!!!!!!!!!!!");
            return;
        }
    }
}

void Tower::updateTowerData(){
    this->updateLevel();
}

void Tower::updateLevel(){
    
}

bool Tower::initTower(){
    if (!Sprite::init()){
        return false;
    }
    
    return true;
}

Tower::~Tower(){
    
}
