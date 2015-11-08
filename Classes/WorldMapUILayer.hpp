//
//  WorldMapUILayer.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/4.
//
//

#ifndef WorldMapUILayer_hpp
#define WorldMapUILayer_hpp

#include <stdio.h>
#include "cocos2d.h"

class WorldMapUILayer : public cocos2d::Layer{
public:
    static WorldMapUILayer *create();
    
    virtual bool init();
    
    void layoutUI();
    
private:
    cocos2d::Sprite *_starLabel;
    cocos2d::Sprite *_diamondLabel;
    
    cocos2d::Menu *_shopButton;
    cocos2d::Menu *_heroRoomButton;
    cocos2d::Menu *_upgradesButton;
    cocos2d::Menu *_encyclopediaButton;
    
    cocos2d::Menu *_achievementButton;
    cocos2d::Menu *_oprationButton;
    cocos2d::Sprite *_oprationButtonBackground;
    cocos2d::Menu *_homeButton;
    cocos2d::Menu *_soundButton;
    cocos2d::Menu *_musicButton;
    
};

#endif /* WorldMapUILayer_hpp */
