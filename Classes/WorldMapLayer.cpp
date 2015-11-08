//
//  WorldMapLayer.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/4.
//
//

#include "WorldMapLayer.hpp"

#include "ResourcesPath.h"

#include "WorldMapGameStage.hpp"

USING_NS_CC;

WorldMapLayer *WorldMapLayer::create(){
    WorldMapLayer *pRet = new (std::nothrow) WorldMapLayer();
    if (pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }
    
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

bool WorldMapLayer::init(){
    if (!Layer::init()){
        return false;
    }
    
    this->layoutWorldMap();
    _worldMapUILayer = WorldMapUILayer::create();
    this->addChild(_worldMapUILayer, 2);
    this->dealMapPositionData();
    
    return true;
}

void WorldMapLayer::onEnter(){
    Layer::onEnter();
    
    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->setSwallowTouches(true);
    _touchListener->onTouchBegan = [&](Touch *touch, Event *event){
        return true;
    };
    _touchListener->onTouchMoved = [&](Touch *touch, Event *event){
        Vec2 delta = touch->getDelta();
        Vec2 mapPosition = _map->getPosition();
        
        if (mapPosition.x + delta.x < 0 && mapPosition.x + delta.x > _mapMinPosition.x){
            _map->setPosition(mapPosition.x + delta.x, mapPosition.y);
        }else if (mapPosition.x + delta.x > 0){
            _map->setPosition(0, mapPosition.y);
        }else if (mapPosition.x + delta.x < _mapMinPosition.x){
            _map->setPosition(_mapMinPosition.x, mapPosition.y);
        }
        
        mapPosition = _map->getPosition();
        
        if (mapPosition.y + delta.y < 0 && mapPosition.y + delta.y > _mapMinPosition.y){
            _map->setPosition(mapPosition.x, mapPosition.y + delta.y);
        }else if (mapPosition.y + delta.y > 0){
            _map->setPosition(mapPosition.x, 0);
        }else if (mapPosition.y + delta.y < _mapMinPosition.y){
            _map->setPosition(mapPosition.x, _mapMinPosition.y);
        }
        
        
    };
    _touchListener->onTouchEnded = [&](Touch *touch, Event *event){
        
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);
    
    //这里先加入第一个关卡做测试
    ValueMap stage1 = _gameLevelObjectGroup->getObject("stage_1");
    CCLOG("第一个关卡的位置 : (%f, %f)", stage1["x"].asFloat(), stage1["y"].asFloat());
    Vec2 stage1Position = Vec2(stage1["x"].asFloat(), stage1["y"].asFloat());
    WorldMapGameStage *stage = WorldMapGameStage::createWithSpriteFrameName("worldmap_gamelevel_flag.png");
    stage->setPosition(stage1Position);
    _map->addChild(stage, 1);
    
}


void WorldMapLayer::moveMapMakePointAtCenter(const cocos2d::Vec2 &point){
    Vec2 pointMapShouldMoveTo = Vec2(_visibleSize.width - point.x, _visibleSize.height - point.y);
    
    if (pointMapShouldMoveTo.x > 0){
        pointMapShouldMoveTo.x = 0;
    }else if (pointMapShouldMoveTo.x < _mapMinPosition.x){
        pointMapShouldMoveTo.x = _mapMinPosition.x;
    }
    
    if (pointMapShouldMoveTo.y > 0){
        pointMapShouldMoveTo.y = 0;
    }else if (pointMapShouldMoveTo.y < _mapMinPosition.y){
        pointMapShouldMoveTo.y = _mapMinPosition.y;
    }
    
    _map->runAction(MoveTo::create(0.1, pointMapShouldMoveTo));
}

void WorldMapLayer::onExit(){
    Layer::onExit();
    if (_touchListener != nullptr){
        Director::getInstance()->getEventDispatcher()->removeEventListener(_touchListener);
    }
}

void WorldMapLayer::dealMapPositionData(){
    _visibleSize = Director::getInstance()->getVisibleSize();
    _mapSize = _map->getContentSize();
    _mapMaxPosition = Vec2(0, 0);
    _mapMinPosition = Vec2(_visibleSize.width - _mapSize.width, _visibleSize.height - _mapSize.height);
}

void WorldMapLayer::layoutWorldMap(){
    
    _worldMap = TMXTiledMap::create(WORLDMAP_TMX);
    _map = cocos2d::Sprite::create(WORLDMAP_MAP);
    _map->setAnchorPoint(Vec2(0, 0));
    _map->setPosition(0, 0);
    this->addChild(_map, 1);
    
    _gameLevelObjectGroup = _worldMap->getObjectGroup("game_level");
    
}
