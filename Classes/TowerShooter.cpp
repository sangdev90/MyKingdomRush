//
//  TowerShooter.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/23.
//
//

#include "TowerShooter.hpp"
#include "GameData.hpp"
USING_NS_CC;

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
