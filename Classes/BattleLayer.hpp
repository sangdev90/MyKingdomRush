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
#include "BattleAStarGridData.hpp"

class BattleUILayer;
class Tower;
class Person;
class Monster;

class BattleLayer : public cocos2d::Layer{
public:
    
#pragma mark - Public Method Member
    BattleLayer(const std::string &stage)
    : _stage(stage) {};
    
    static BattleLayer *create(const std::string &stage);
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
    cocos2d::Vec2 getSomethingOnMapWorldPoint(cocos2d::Sprite *node);
    
#pragma mark - Public Data Member
    std::vector<Tower *> towerArray;
    std::vector<Monster *> monsterArray;
    
private:
    
#pragma mark - Private Data Member
    const std::string _stage;
    
    BattleUILayer *_battleUILayer;
    cocos2d::Sprite *_battleMap;
    BattleData _battleData;
    std::vector<BattleAStarGridData> _battleAStarData;
    std::vector<std::vector<std::vector<cocos2d::Vec2>>> _battlePathData;
    
    cocos2d::Size _mapSize;
    cocos2d::Size _visibleSize;
    cocos2d::Vec2 _mapMinPosition;
    cocos2d::Vec2 _mapMaxPosition;
    float _currentMapScale;
    float _mapMinScale;
    float _mapMaxScale;
    cocos2d::EventListenerTouchAllAtOnce *_touchListener;
    
#pragma mark - Private Method Member
    void _loadBattle();
    void _dealMapPositoinData();
    void _dealMapScaleData();
    void _loadBattleData();
    void _getMapRoad();
    
    
#pragma mark - Some Test Code
    void _drawSomthingOnMap();
    cocos2d::DrawNode *_testDrawNode;
    void _someTestCode();
    void _someTestCodeSchedule();
};

#endif /* BattleLayer_hpp */
