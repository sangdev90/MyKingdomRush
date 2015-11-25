//
//  Tower.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/21.
//
//

#include "Tower.hpp"

USING_NS_CC;

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