//
//  TowerActor.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/23.
//
//

#ifndef TowerActor_hpp
#define TowerActor_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "GameData.hpp"
#include "TowerActorData.hpp"

class TowerShooter;

class TowerActor : public cocos2d::Sprite{
public:
    static TowerActor *createTowerActorByName(const std::string &name);
    
    TowerActor(const std::string &name, const std::string &level):
    _name(name), _level(level) {
        _towerActorData = GameData::getInstance()->getTowerActorDataByNameAndLevel(_name, _level);
    };
    virtual ~TowerActor() = 0;
    
    virtual void attack(const cocos2d::Vec2 &from, const cocos2d::Vec2 &to, const std::function<void ()> &attackCallback) = 0;
    
    virtual void updateTowerLevel(const std::string &level);
    
protected:
    
    std::string _name;
    std::string _level;
    TowerActorData _towerActorData;
    
};

#endif /* TowerActor_hpp */
