//
//  WorldMapGameStage.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/6.
//
//

#ifndef WorldMapGameStage_hpp
#define WorldMapGameStage_hpp

#include <stdio.h>
#include "cocos2d.h"

/// 世界地图上的关卡，这个精灵只能由精灵帧名字创建，但是这里并没有隐藏从 cocos2d::Sprite 继承而来的工厂方法，严格来说这些方法应该被隐藏
class WorldMapGameStage : public cocos2d::Sprite{
public:
    
    WorldMapGameStage(const std::string &frameName);
    
    static WorldMapGameStage *createWithSpriteFrameName(const std::string &frameName);
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
private:
    cocos2d::Sprite *_displaySrpite;
    cocos2d::EventListenerTouchOneByOne *_touchListener;
};

#endif /* WorldMapGameStage_hpp */
