//
//  WorldMapGameStage.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/6.
//
//

#include "WorldMapGameStage.hpp"

USING_NS_CC;

WorldMapGameStage::WorldMapGameStage(const std::string &frameName){
    _displaySrpite = Sprite::createWithSpriteFrameName(frameName);
    this->addChild(_displaySrpite);
}

WorldMapGameStage *WorldMapGameStage::createWithSpriteFrameName(const std::string &frameName){
    WorldMapGameStage *pRet = new (std::nothrow) WorldMapGameStage(frameName);
    if (pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }
    
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

bool WorldMapGameStage::init(){
    if (!Sprite::init()){
        return false;
    }
    
    return true;
}

void WorldMapGameStage::onEnter(){
    Sprite::onEnter();
    
    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->setSwallowTouches(true);
    _touchListener->onTouchBegan = [&](Touch *touch, Event *event){
        Vec2 locationPosition = this->convertToNodeSpace(touch->getLocation());
        Size thisRealSize = _displaySrpite->getContentSize();
        Rect nodeRect = Rect(-thisRealSize.width / 2, -thisRealSize.height / 2, thisRealSize.width, thisRealSize.height);
        if (nodeRect.containsPoint(locationPosition)){
            CCLOG("Touch Game Stage");
            
            return true;
        }
        return false;
    };
    _touchListener->onTouchMoved = [](Touch *touch, Event *event){
        
    };
    _touchListener->onTouchEnded = [](Touch *touch, Event *event){
        
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);
}

void WorldMapGameStage::onExit(){
    Sprite::onExit();
    
    if (_touchListener){
        Director::getInstance()->getEventDispatcher()->removeEventListener(_touchListener);
    }
}