//
//  WorldMapScene.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/4.
//
//

#include "WorldMapScene.hpp"
#include "ToolFunction.hpp"

USING_NS_CC;

WorldMapScene *WorldMapScene::create(){
    WorldMapScene *pRet = new (std::nothrow) WorldMapScene();
    if (pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }
    
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

bool WorldMapScene::init(){
    if (!Scene::init()){
        return false;
    }
    
    CCLOG("WorldMapScene init");
    
    loadWorldMapSpriteSheet();
    
    _worldMapLayer = WorldMapLayer::create();
    this->addChild(_worldMapLayer, 1);
    
    
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    TMXTiledMap *testMap = TMXTiledMap::create("res/image/worldmap/map/worldmap.tmx");
//    testMap->setAnchorPoint(Vec2(0.5, 0.5));
//    testMap->setPosition(visibleSize.width / 2, visibleSize.height / 2);
//    this->addChild(testMap, 1);
//    
//    Sprite *testDiamond = Sprite::create("res/image/worldmap/map/testdiamond.png");
//    testDiamond->setPosition(visibleSize.width / 2, visibleSize.height / 2);
//    testMap->addChild(testDiamond);
    
    return true;
}
