//
//  TowerShootThing.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/23.
//
//

#ifndef TowerShootThing_hpp
#define TowerShootThing_hpp

#include <stdio.h>
#include "cocos2d.h"

class TowerShootThing : public cocos2d::Sprite{
public:
    
    static TowerShootThing *createTowerShootThingByNameAndLevel(const std::string &name, const  std::string &level);
    
    TowerShootThing(const std::string &name, const std::string &level):
    _name(name), _level(level) {};
    virtual ~TowerShootThing() = 0;
    
    virtual void attack(const cocos2d::Vec2 &from, const cocos2d::Vec2 &to, const std::function<void ()> &attackCallback) = 0;
    
    
protected:
    
    std::string _name;
    std::string _level;
};

#endif /* TowerShootThing_hpp */
