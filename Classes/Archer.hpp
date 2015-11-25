//
//  Archer.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/25.
//
//

#ifndef Archer_hpp
#define Archer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "TowerShooter.hpp"

class Archer : public TowerShooter{
public:
    
    static Archer *createArcher();
    
    Archer():
    TowerShooter("archer", "level1") {};
    ~Archer() = default;
    
    bool initArcher();
    
    virtual void attack(const cocos2d::Vec2 &from, const cocos2d::Vec2 &to, const std::function<void ()> &attackCallback);
    virtual void updateTowerShooterLevel(const std::string &level);
    
    
private:
    cocos2d::Vector<cocos2d::SpriteFrame *> _attackUpSpriteFrameArray;
    cocos2d::Vector<cocos2d::SpriteFrame *> _attackDownSpriteFrameArray;
};

#endif /* Archer_hpp */
