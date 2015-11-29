//
//  TowerShootThing.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/23.
//
//

#include "TowerShootThing.hpp"
#include "ToolFunction.hpp"
#include "GameData.hpp"

#include "Arrow.hpp"
#include "Magic.hpp"
#include "Bomb.hpp"


USING_NS_CC;

TowerShootThing::~TowerShootThing(){
    
}

TowerShootThing *TowerShootThing::createTowerShootThingByNameAndLevel(const std::string &name, const std::string &level){
    
    if (name == "arrow"){
        return Arrow::createArrowByLevel(level);
    }
    
    if (name == "magic"){
        
    }
    
    if (name == "bomb"){
        
    }
    
    CCLOG("要创建一个不知名的 Tower Shoot Thing : %s", name.c_str());
    return nullptr;
    
}
