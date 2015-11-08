//
//  BattleUILayer.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/8.
//
//

#include "BattleUILayer.hpp"
#include "ToolFunction.hpp"
#include "BattleDisplayBoardSprite.hpp"

BattleUILayer *BattleUILayer::create(){
    BattleUILayer *pRet = new (std::nothrow) BattleUILayer();
    if (pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }
    
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

bool BattleUILayer::init(){
    if (!Layer::init()){
        return false;
    }
    
    return true;
}

void BattleUILayer::layoutUI(){
    
}
