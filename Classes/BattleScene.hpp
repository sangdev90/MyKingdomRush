//
//  BattleScene.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/8.
//
//

#ifndef BattleScene_hpp
#define BattleScene_hpp

#include <stdio.h>
#include "cocos2d.h"

class BattleLayer;

class BattleScene : public cocos2d::Scene{
public:
    
    BattleScene(const std::string &stage)
    : _stage(stage) {};
    
    static BattleScene *create(const std::string &stage);
    
    virtual bool init();
    
private:
    std::string _stage;
    
    BattleLayer *_battleLayer;
    
};

#endif /* BattleScene_hpp */
