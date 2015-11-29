//
//  Monster.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/14.
//
//

#include <math.h>

#include "Monster.hpp"
#include "GameData.hpp"
#include "ToolFunction.hpp"

USING_NS_CC;

Monster *Monster::createWithName(const std::string &name, const std::vector<cocos2d::Vec2> &path){
    Monster *pRet = new (std::nothrow) Monster(name);
    if (pRet && pRet->init()){
        pRet->autorelease();
        pRet->setPath(path);
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
    this->setPosition(_pathVector[0].x, _pathVector[0].y);
    _actionSprite = Sprite::createWithSpriteFrameName(getMonsterAnimationFrameName(_name, "run_toward", 0));
    _actionSprite->setScale(1.5, 1.5);
    this->addChild(_actionSprite);
    this->scheduleUpdate();
    
    _currentRunTargetPointIndex = 0;
    _nextRunTargetPointIndex = 1;
    _currentRunTargetPoint = _pathVector.at(_currentRunTargetPointIndex);
    _nextRunTargetPoint = _pathVector.at(_nextRunTargetPointIndex);
    _faceTo = "right";
    this->run();
    
//    CCLOG("小兵的路径");
//    for (int i = 0; i < _pathVector.size(); ++i){
//        CCLOG("(%.2f, %.2f)", _pathVector[i].x, _pathVector[i].y);
//    }
    
}

void Monster::onExit(){
    Sprite::onExit();
    this->unscheduleUpdate();
}

void Monster::run(){
    _makeFaceTo();
    float duration = distanceBetweenTwoVec2(_currentRunTargetPoint, _nextRunTargetPoint) / (float)_runSpeed;
    MoveTo *runMoveToAction = MoveTo::create(duration, _nextRunTargetPoint);
    ++_currentRunTargetPointIndex;
    _nextRunTargetPointIndex = _currentRunTargetPointIndex + 1;
    if (_nextRunTargetPointIndex == _pathVector.size()){
        this->removeFromParentAndCleanup(true);
    }
    _currentRunTargetPoint = _pathVector[_currentRunTargetPointIndex];
    _nextRunTargetPoint = _pathVector[_nextRunTargetPointIndex];
    
    Animation *runAnimation;
    if (_faceTo == "left"){
        _actionSprite->setFlippedX(true);
        runAnimation = Animation::createWithSpriteFrames(_runTowardAnimationFrameArray);
    }else if (_faceTo == "right"){
        _actionSprite->setFlippedX(false);
        runAnimation = Animation::createWithSpriteFrames(_runTowardAnimationFrameArray);
    }else if (_faceTo == "forward"){
        runAnimation = Animation::createWithSpriteFrames(_runForwardAnimationFrameArray);
    }else if (_faceTo == "backward"){
        runAnimation = Animation::createWithSpriteFrames(_runBackwardAnimationFrameArray);
    }
    
    runAnimation->setDelayPerUnit(GameData::getInstance()->defaultDelayPerUnit);
    Animate *animate = Animate::create(runAnimation);
    _actionSprite->stopAllActions();
    _actionSprite->runAction(RepeatForever::create(animate));

    
    this->runAction(Sequence::create(runMoveToAction,
                                     CallFunc::create([&](){
                                        this->run();
                                    }), NULL));
    
}

void Monster::attack(Person *attackTarget){
    
}

void Monster::die(){
    
}

void Monster::update(float dt){
//    Vec2 currentPosition = this->getPosition();
//    CCLOG("(%.2f, %.2f)", currentPosition.x, currentPosition.y);
    this->setLocalZOrder(getBattleLocalZOrderByActor(this));
}

void Monster::_initMonsterData(){
    _side = "monster";
    _myMonsterData = GameData::getInstance()->getMonsterDataByMonsterName(_name);
    printMonsterData(_myMonsterData);
    _runSpeed = _myMonsterData.speed;
    _runSpeed = 30;
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

void Monster::_makeFaceTo(){
    
    if (fabsf(_currentRunTargetPoint.x - _nextRunTargetPoint.x) > fabsf(_currentRunTargetPoint.y - _nextRunTargetPoint.y)){
        if (_nextRunTargetPoint.x < _currentRunTargetPoint.x){
            _faceTo = "left";
        }else {
            _faceTo = "right";
        }
    }else {
        if (_nextRunTargetPoint.y < _currentRunTargetPoint.y){
            _faceTo = "forward";
        }else {
            _faceTo = "backward";
        }
    }
    
}













