//
//  BattleScene.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/8.
//
//

#include "BattleScene.hpp"
#include "ToolFunction.hpp"
#include "BattleLayer.hpp"

USING_NS_CC;

BattleScene *BattleScene::create(const std::string &stage){
    BattleScene *pRet = new (std::nothrow) BattleScene(stage);
    if (pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }
    
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

bool BattleScene::init(){
    if (!Scene::init()){
        return false;
    }
    
    prepareBattle();
    
    _battleLayer = BattleLayer::create(_stage);
    this->addChild(_battleLayer);
    
    return true;
}
