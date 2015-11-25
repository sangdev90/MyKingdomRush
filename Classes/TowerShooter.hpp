//
//  TowerShooter.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/23.
//
//

#ifndef TowerShooter_hpp
#define TowerShooter_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "TowerShooterData.hpp"

class TowerShooter : public cocos2d::Sprite{
public:
    
    static TowerShooter *createTowerShooterByName(const std::string &name);
    
    TowerShooter(const std::string &name, const std::string &level):
    _name(name), _level(level) {};
    virtual ~TowerShooter() = 0;
    
    virtual void attack(const cocos2d::Vec2 &from, const cocos2d::Vec2 &to, const std::function<void ()> &attackCallback) = 0;
    
    virtual void updateTowerShooterLevel(const std::string &level);
    
protected:
    
    std::string _name;
    std::string _level;
    TowerShooterData _towerShooterData;
    
};

#endif /* TowerShooter_hpp */
