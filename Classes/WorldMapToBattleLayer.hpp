//
//  WorldMapToBattleLayer.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/7.
//
//

#ifndef WorldMapToBattleLayer_hpp
#define WorldMapToBattleLayer_hpp

#include <stdio.h>
#include "cocos2d.h"

class WorldMapToBattleLayer : public cocos2d::Layer{
public:
    
    WorldMapToBattleLayer(const std::string &stage)
    : _battleStage(stage) {};
    
    static WorldMapToBattleLayer *create(const std::string &stage);
    
    virtual bool init();
    virtual void onExit();
    virtual void onEnter();
    
    void layoutUI();
    
private:
    
    std::string _battleStage;
    
    cocos2d::Sprite *_background;
    cocos2d::Sprite *_perViewBackground;
    cocos2d::Sprite *_smallBattleMap;
    cocos2d::Menu *_closeButton;
    cocos2d::Menu *_toBattleButton;
    
};

#endif /* WorldMapToBattleLayer_hpp */
