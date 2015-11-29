//
//  Arrow.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/26.
//
//

#ifndef Arrow_hpp
#define Arrow_hpp

#include <stdio.h>
#include "TowerShootThing.hpp"

class Arrow : public TowerShootThing{
public:
    
    static Arrow *createArrowByLevel(const std::string &level);
    
    Arrow(const std::string &level):
    TowerShootThing("arrow", level) {};
    
    bool initArrow();
    
    virtual void attack(const cocos2d::Vec2 &from, const cocos2d::Vec2 &to, const std::function<void ()> &attackCallback);
    
private:
};

#endif /* Arrow_hpp */
