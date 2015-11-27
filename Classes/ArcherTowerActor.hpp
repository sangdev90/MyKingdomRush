//
//  ArcherTowerActor.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/25.
//
//

#ifndef ArcherTowerActor_hpp
#define ArcherTowerActor_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "TowerActor.hpp"

class TowerShooter;

class ArcherTowerActor : public TowerActor{
public:
    
    static ArcherTowerActor *createArcherTowerActor();
    
    ArcherTowerActor():
    TowerActor::TowerActor("archer_tower", "level1") {
        
        //TODO: 这里 create TowerShooter
        
    };
    ~ArcherTowerActor() = default;
    
    bool initArcherTowerActor();
    
    virtual void attack(const cocos2d::Vec2 &from, const cocos2d::Vec2 &to, const std::function<void ()> &attackCallback);
    virtual void updateTowerLevel(const std::string &level);
    
    
private:
    
    TowerShooter *_leftTowerShooter;
    TowerShooter *_rightTowerShooter;
    
};

#endif /* ArcherTowerActor_hpp */
