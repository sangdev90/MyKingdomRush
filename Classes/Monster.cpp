//
//  Monster.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/14.
//
//

#include "Monster.hpp"
#include "GameData.hpp"
#include "ToolFunction.hpp"

USING_NS_CC;

Monster *Monster::createWithName(const std::string &name){
    Monster *pRet = new (std::nothrow) Monster(name);
    if (pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }
    
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

bool Monster::init(){
    
    if (!Sprite::init()){
        return false;
    }
    CCLOG("Init %s", _name.c_str());
    _initMonsterData();
    _initBattleMapData();
    _initAnimationData();
    
    
    return true;
}

void Monster::onEnter(){
    Sprite::onEnter();
}

void Monster::onExit(){
    Sprite::onExit();
}

void Monster::run(){
    
}

void Monster::attack(Person *attackTarget){
    
}

void Monster::die(){
    
}

void Monster::_initMonsterData(){
    _side = "monster";
    _myMonsterData = GameData::getInstance()->getMonsterDataByMonsterName(_name);
    printMonsterData(_myMonsterData);
    
}

void Monster::_initBattleMapData(){
    
}

void Monster::_initAnimationData(){
    
    //run_toward
    for (int frameIndex = 0; frameIndex < _myMonsterData.numberOfTowardFrame; ++frameIndex){
        std::string frameName = getMonsterAnimationFrameName(_name, "run_toward", frameIndex);
        _runTowardAnimationFrameArray.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
    }
    
    //run_forward
    for (int frameIndex = 0; frameIndex < _myMonsterData.numberOfForwardFrame; ++frameIndex){
        std::string frameName = getMonsterAnimationFrameName(_name, "run_forward", frameIndex);
        _runForwardAnimationFrameArray.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
    }
    
    //run_backward
    for (int frameIndex = 0; frameIndex < _myMonsterData.numberOfBcakwardFrame; ++frameIndex){
        std::string frameName = getMonsterAnimationFrameName(_name, "run_backward", frameIndex);
        _runBackwardAnimationFrameArray.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
    }
    
    //attack
    for (int frameIndex = 0; frameIndex < _myMonsterData.numberOfAttackFrame; ++frameIndex){
        std::string frameName = getMonsterAnimationFrameName(_name, "attack", frameIndex);
        _attackAniamtionFrameArray.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
    }
    
    //die
    for (int frameIndex = 0; frameIndex < _myMonsterData.numberOfDieFrame; ++frameIndex){
        std::string frameName = getMonsterAnimationFrameName(_name, "die", frameIndex);
        _dieAnimationFrameArray.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
    }
    
    
}














