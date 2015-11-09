//
//  BattleLayer.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/8.
//
//

#include "BattleLayer.hpp"
#include "BattleUILayer.hpp"

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
    this->addChild(_battleUILayer);
    
    return true;
}