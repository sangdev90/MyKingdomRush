//
//  BattleLayer.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/8.
//
//

#ifndef BattleLayer_hpp
#define BattleLayer_hpp

#include <stdio.h>
#include "cocos2d.h"

class BattleUILayer;

class BattleLayer : public cocos2d::Layer{
public:
    
    BattleLayer(const std::string &stage)
    : _stage(stage) {};
    
    static BattleLayer *create(const std::string &stage);
    
    virtual bool init();
    
private:
    const std::string _stage;
    
    BattleUILayer *_battleUILayer;
    cocos2d::Sprite *_battleMap;
};

#endif /* BattleLayer_hpp */
