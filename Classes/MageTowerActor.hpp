//
//  MageTowerActor.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/25.
//
//

#ifndef MageTowerActor_hpp
#define MageTowerActor_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "TowerActor.hpp"

class TowerShooter;

class MageTowerActor : public TowerActor{
public:
    static MageTowerActor *createMageTowerActor();
    
    MageTowerActor():
    TowerActor("mage_tower", "level1") {
        //TODO: 这里 create TowerShooter
    };
    ~MageTowerActor() = default;
    
    void initMageTowerActor();
    
    virtual void attack(const cocos2d::Vec2 &from, const cocos2d::Vec2 &to, std::function<void ()>);
    virtual void updateTowerLevel(const std::string &level);
    
private:
    
    TowerShooter *centerTowerShooter;
    
};

#endif /* MageTowerActor_hpp */
