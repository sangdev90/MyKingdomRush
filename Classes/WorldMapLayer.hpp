//
//  WorldMapLayer.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/4.
//
//

#ifndef WorldMapLayer_hpp
#define WorldMapLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "WorldMapUILayer.hpp"

class WorldMapLayer : public cocos2d::Layer{
public:
    static WorldMapLayer *create();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    
    void layoutWorldMap();
    void dealMapPositionData();
    
    /**
     *  移动地图，使传入的点尽量位于屏幕中央
     *
     *  @param point Vec2
     */
    void moveMapMakePointAtCenter(const cocos2d::Vec2 &point);
    
private:
    WorldMapUILayer *_worldMapUILayer;
    cocos2d::TMXTiledMap *_worldMap;
    cocos2d::Sprite *_map;
    cocos2d::TMXObjectGroup *_gameLevelObjectGroup;
    cocos2d::EventListenerTouchOneByOne *_touchListener;
    
    cocos2d::Size _visibleSize;
    cocos2d::Size _mapSize;
    cocos2d::Vec2 _mapMinPosition;
    cocos2d::Vec2 _mapMaxPosition;
};

#endif /* WorldMapLayer_hpp */
