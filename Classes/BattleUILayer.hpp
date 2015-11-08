//
//  BattleUILayer.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/8.
//
//

#ifndef BattleUILayer_hpp
#define BattleUILayer_hpp

#include <stdio.h>
#include "cocos2d.h"

class BattleUILayer : public cocos2d::Layer{
public:
    
    static BattleUILayer *create();
    
    virtual bool init();
    
private:
};

#endif /* BattleUILayer_hpp */
