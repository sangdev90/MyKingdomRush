//
//  BattleLifeBarSprite.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/12/27.
//
//

#ifndef BattleLifeBarSprite_hpp
#define BattleLifeBarSprite_hpp

#include <stdio.h>
#include "cocos2d.h"

enum{
    battle_life_bar_big = 0,
    battle_life_bar_med,
    battle_life_bar_small,
    battle_life_bar_medBig,
};

class BattleLifeBarSprite : public cocos2d::Sprite{
public:
    static BattleLifeBarSprite *createBattleLifeBarSprite(int state, int fullLiftPoint);
    
    BattleLifeBarSprite(int state, int fullLifePoint):
    _state(state), _fullLifePoint(fullLifePoint) {}
    
    virtual bool init();
    
    void updateLife(int targetValue);
    
private:
    int _state = 0;
    
    int _fullLifePoint = 0;
    int _currentLifePoint = 0;
    
    cocos2d::Sprite *_fullLifeBar;
    cocos2d::Sprite *_currentLifeBar;
    
    /**
     *  得到血条素材名字
     *
     *  @param which 指明了要哪个，是 background 还是 normal
     *
     *  @return 血条素材名
     */
    std::string _getLifeBarSpriteFrameName(const std::string &which);
};

#endif /* BattleLifeBarSprite_hpp */
