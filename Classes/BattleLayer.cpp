//
//  BattleLayer.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/8.
//
//

#include <vector>
#include "BattleLayer.hpp"
#include "BattleUILayer.hpp"

#include "ResourcesPath.h"
#include "ToolFunction.cpp"

USING_NS_CC;

BattleLayer *BattleLayer::create(const std::string &stage){
    BattleLayer *pRet = new (std::nothrow) BattleLayer(stage);
    if (pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }
    
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

bool BattleLayer::init(){
    if (!Layer::init()){
        return false;
    }
    
    _battleUILayer = BattleUILayer::create();
    this->addChild(_battleUILayer, 100);
    
    this->_loadBattle();
    this->_dealMapPositoinData();
    this->_dealMapScaleData();
    
    CCLOG("Tile Map Size (%f, %f)", _battleTMXMap->getMapSize().width, _battleTMXMap->getMapSize().height);
    CCLOG("Tile Map (%f, %f)", _battleTMXMap->getTileSize().width, _battleTMXMap->getTileSize().height);
    
    
    
    return true;
}

void BattleLayer::onEnter(){
    Layer::onEnter();
    
    _touchListener = EventListenerTouchAllAtOnce::create();
    _touchListener->onTouchesBegan = [&](const std::vector<Touch *> &touches, Event *event){
        
        if (touches.size() == 1){
            Vec2 touchPosition = _battleMap->convertToNodeSpace(touches[0]->getLocation());
            CCLOG("Touch Position (%f, %f)", touchPosition.x, touchPosition.y);
            int tileX = touchPosition.x / _battleTMXMap->getTileSize().width;
            int tileY = ((_battleTMXMap->getMapSize().height * _battleTMXMap->getTileSize().height) - touchPosition.y) / _battleTMXMap->getTileSize().height;
            CCLOG("Tile (%d, %d)", tileX, tileY);
            int tileID = _roadLayer1->getTileGIDAt(Vec2(tileX, tileY));
            CCLOG("TileID %d", tileID);
            if (tileID){
                Value prop = _battleTMXMap->getPropertiesForGID(tileID);
                ValueMap propValueMap = prop.asValueMap();
                CCLOG("Is Road %s", propValueMap["road"].asString().c_str());
            }
        }
        
    };
    _touchListener->onTouchesMoved = [&](const std::vector<Touch *> &touches, Event *event){
        if (touches.size() == 1){
            Touch *touch = touches[0];
            Vec2 mapPosition = _battleMap->getPosition();
            Vec2 delta = touch->getDelta();
            if (mapPosition.x + delta.x > _mapMinPosition.x && mapPosition.x + delta.x < _mapMaxPosition.x){
                _battleMap->setPosition(mapPosition.x + delta.x, mapPosition.y);
            }else if (mapPosition.x + delta.x < _mapMinPosition.x){
                _battleMap->setPosition(_mapMinPosition.x, mapPosition.y);
            }else if (mapPosition.x + delta.x > _mapMaxPosition.x){
                _battleMap->setPosition(_mapMaxPosition.x, mapPosition.y);
            }
            
            mapPosition = _battleMap->getPosition();
            if (mapPosition.y + delta.y > _mapMinPosition.y && mapPosition.y + delta.y < _mapMaxPosition.y){
                _battleMap->setPosition(mapPosition.x, mapPosition.y + delta.y);
            }else if (mapPosition.y + delta.y < _mapMinPosition.y){
                _battleMap->setPosition(mapPosition.x, _mapMinPosition.y);
            }else if (mapPosition.y + delta.y > _mapMaxPosition.y){
                _battleMap->setPosition(mapPosition.x, _mapMaxPosition.y);
            }
        }
        
        if (touches.size() == 2){
            Touch *touch1 = touches[0];
            Touch *touch2 = touches[1];
            float previousDistance = distanceBetweenTwoVec2(touch1->getPreviousLocation(), touch2->getPreviousLocation());
            float distance = distanceBetweenTwoVec2(touch1->getLocation(), touch2->getLocation());
            if (fabsf(distance - previousDistance) < 5){
                return;
            }else {
                float scale = _battleMap->getScale() * (distance / previousDistance);
                if (scale > _mapMaxScale || scale < _mapMinScale){
                    return;
                }
                _battleMap->setScale(scale);
                this->_dealMapPositoinData();
                Vec2 currentbBattleMapPosition = _battleMap->getPosition();
                Size currentBattleMapSize = Size(_battleMap->getContentSize().width * _currentMapScale, _battleMap->getContentSize().height * _currentMapScale);
                if (currentbBattleMapPosition.x - currentBattleMapSize.width / 2 > 0){
                    _battleMap->setPosition(currentBattleMapSize.width / 2, currentbBattleMapPosition.y);
                }
                if (currentbBattleMapPosition.x + currentBattleMapSize.width / 2 < _visibleSize.width){
                    _battleMap->setPosition(_visibleSize.width - currentBattleMapSize.width / 2, currentbBattleMapPosition.y);
                }
                
                currentbBattleMapPosition = _battleMap->getPosition();
                if (currentbBattleMapPosition.y - currentBattleMapSize.height / 2 > 0){
                    _battleMap->setPosition(currentbBattleMapPosition.x, currentBattleMapSize.height / 2);
                }
                if (currentbBattleMapPosition.y + currentBattleMapSize.height / 2 < _visibleSize.height){
                    _battleMap->setPosition(currentbBattleMapPosition.x, _visibleSize.height - currentBattleMapSize.height / 2);
                }

            }
        }
        
    };
    _touchListener->onTouchesEnded = [](const std::vector<Touch *> &touches, Event *evnet){
        
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);
}

void BattleLayer::onExit(){
    Layer::onExit();
    if (_touchListener){
        Director::getInstance()->getEventDispatcher()->removeEventListener(_touchListener);
    }
}

void BattleLayer::_loadBattle(){
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    _battleMap = Sprite::create(BATTLE_MAP_STAGE_1);
    _battleTMXMap = TMXTiledMap::create(BATTLE_TMXMAP_STAGE_1);
    _roadLayer1 = _battleTMXMap->getLayer("road_1");
    if (_roadLayer1 == nullptr){
        CCLOG("Can't get RoadLayer");
    }
    _mapSize = _battleMap->getContentSize();
    _battleMap->setScale(0.8);
    _currentMapScale = 0.8;
    _battleMap->setPosition(_visibleSize.width / 2, _visibleSize.height / 2);
    this->addChild(_battleMap, 1);
    
    _battleTMXMap->setPosition(0, 0);
    _battleMap->addChild(_battleTMXMap);
    
}

void BattleLayer::_dealMapPositoinData(){
    
    _currentMapScale = _battleMap->getScale();
    
    _mapMinPosition = Vec2(_visibleSize.width - _mapSize.width * _currentMapScale / 2, _visibleSize.height - _mapSize.height * _currentMapScale / 2);
    _mapMaxPosition = Vec2(_mapSize.width * _currentMapScale / 2, _mapSize.height * _currentMapScale / 2);
}

void BattleLayer::_dealMapScaleData(){
    _mapMaxScale = 1;
    
    float widthScale = _visibleSize.width / _mapSize.width;
    float heightScale = _visibleSize.height / _mapSize.height;
    
    _mapMinScale = widthScale > heightScale ? widthScale : heightScale;
    
    CCLOG("Min Scale %f", _mapMinScale);
}


















