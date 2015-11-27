//
//  TowerShooter.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/23.
//
//

#include "TowerShooter.hpp"
#include "GameData.hpp"

#include "Archer.hpp"
#include "Mage.hpp"

USING_NS_CC;

TowerShooter *TowerShooter::createTowerShooterByName(const std::string &name){
    
    if (name == GameData::getInstance()->towerShooterName.archer){
        return Archer::createArcher();
    }
    
    if (name == GameData::getInstance()->towerShooterName.mage){
        
    }
    
    CCLOG("要创建一个不知名的 Tower Shooter : %s", name.c_str());
    return nullptr;
    
}


TowerShooter::~TowerShooter(){}

void TowerShooter::updateTowerShooterLevel(const std::string &level){
    if (level == "level41" || level == "level42"){
        if (level == "level3"){
            _level = level;
        }else {
            CCLOG("射手要跳级升，这是不对的！！！！！！");
        }
    }else {
        if (_level == GameData::getInstance()->towerLevelTag.level1){
            _level = GameData::getInstance()->towerLevelTag.level2;
        }else if (_level == GameData::getInstance()->towerLevelTag.level2){
            _level = GameData::getInstance()->towerLevelTag.level3;
        }else {
            CCLOG("TowerShooter 的 Level 有问题！！！");
        }
    }
}
