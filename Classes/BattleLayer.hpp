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
#include "BattleData.hpp"

class BattleUILayer;

class BattleLayer : public cocos2d::Layer{
public:
    
    BattleLayer(const std::string &stage)
    : _stage(stage) {};
    
    static BattleLayer *create(const std::string &stage);
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
private:
    const std::string _stage;
    
    BattleUILayer *_battleUILayer;
    cocos2d::Sprite *_battleMap;
    BattleData _battleData;
    
    cocos2d::Size _mapSize;
    cocos2d::Size _visibleSize;
    cocos2d::Vec2 _mapMinPosition;
    cocos2d::Vec2 _mapMaxPosition;
    float _currentMapScale;
    float _mapMinScale;
    float _mapMaxScale;
    cocos2d::EventListenerTouchAllAtOnce *_touchListener;
    
    void _loadBattle();
    void _dealMapPositoinData();
    void _dealMapScaleData();
    void _loadBattleData();
    void _getMapRoad();
    
    //Draw Test
    void _drawSomthingOnMap();
    cocos2d::DrawNode *_testDrawNode;
    std::vector<cocos2d::Vec2> _testRoadPointVector =
    {   cocos2d::Vec2(2015, 829),
        cocos2d::Vec2(1488, 853),
        cocos2d::Vec2(1336, 1051),
        cocos2d::Vec2(993, 1133),
        cocos2d::Vec2(714, 1040),
        cocos2d::Vec2(592, 859),
        cocos2d::Vec2(132, 862)
    };
};

#endif /* BattleLayer_hpp */
