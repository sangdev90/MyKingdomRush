//
//  Tower.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/21.
//
//

#ifndef Tower_hpp
#define Tower_hpp

#include <stdio.h>
#include "cocos2d.h"

#include "ToolFunction.hpp"
#include "ResourcesPath.h"
#include "GameData.hpp"
#include "TowerData.hpp"

class BattleLayer;
class TowerActor;

class Tower : public cocos2d::Sprite{
public:
    
    static Tower *createTowerByName(const std::string &name, BattleLayer *battleLayer);
    
    Tower(const std::string &name):
    _name(name), _level("level1") {};
    virtual ~Tower() = 0;
    
    void changeLevel(const std::string &levelTag = "");
    void updateTowerData();
    void setBattleLayerPointer(BattleLayer *battleLayer){
        _battleLayerPointer = battleLayer;
    };
    
    virtual void updateLevel();
    virtual bool initTower();
    
protected:
    
    BattleLayer *_battleLayerPointer;
    
    std::string _name;
    std::string _level = "level1";
    std::string _info;
    
    TowerActor *_towerActor;
};


#endif /* Tower_hpp */
