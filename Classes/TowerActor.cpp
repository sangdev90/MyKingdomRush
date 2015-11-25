//
//  TowerActor.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/23.
//
//

#include "TowerActor.hpp"
#include "GameData.hpp"

void TowerActor::updateTowerLevel(const std::string &level){
    if (level == "level41" || level == "level42"){
        if (level == "level3"){
            _level = level;
        }else {
            CCLOG("塔要跳级升，这是不对的！！！！！！");
        }
    }else {
        if (_level == GameData::getInstance()->towerLevelTag.level1){
            _level = GameData::getInstance()->towerLevelTag.level2;
        }else if (_level == GameData::getInstance()->towerLevelTag.level2){
            _level = GameData::getInstance()->towerLevelTag.level3;
        }else {
            CCLOG("TowerActor 的 Level 有问题！！！");
        }
    }
}

TowerActor::~TowerActor(){};
