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
#include "PersonActor.hpp"
#include "MonsterActor.hpp"
#include "BattleLifeBarSprite.hpp"

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
    
    if (!Person::init()){
        return false;
    }
    
//    CCLOG("Init %s", _name.c_str());
    _initMonsterData();
    _initAnimationData();
    _initMonsterActor();
    _initLifeBar();
    _initBattleMapData();
    
    //MARK:Test
    _testCode();
    
    return true;
}

void Monster::onEnter(){
    Person::onEnter();
    this->setPosition(_pathVector[0].x, _pathVector[0].y);
    
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
    Person::onExit();
    this->unscheduleUpdate();
}

void Monster::run(){
    _makeFaceTo();
    
    //位置的移动
    float duration = distanceBetweenTwoVec2(_currentRunTargetPoint, _nextRunTargetPoint) / (float)_runSpeed;
    MoveTo *runMoveToAction = MoveTo::create(duration, _nextRunTargetPoint);
    ++_currentRunTargetPointIndex;
    _nextRunTargetPointIndex = _currentRunTargetPointIndex + 1;
    if (_nextRunTargetPointIndex == _pathVector.size()){
        this->removeFromParentAndCleanup(true);
    }
    _currentRunTargetPoint = _pathVector[_currentRunTargetPointIndex];
    _nextRunTargetPoint = _pathVector[_nextRunTargetPointIndex];
    this->runAction(Sequence::create(runMoveToAction,
                                     CallFunc::create([&](){
        this->run();
    }), NULL));
    
    //动画的表演
    if (_faceTo == "left"){
        _personActor->turnAround(_faceTo);
        _personActor->playTowardAnimation([](){});
    }else if (_faceTo == "right"){
        _personActor->turnAround(_faceTo);
        _personActor->playTowardAnimation([](){});
    }else if (_faceTo == "forward"){
        _personActor->playForwardAnimation([](){});
    }else if (_faceTo == "backward"){
        _personActor->playBackwardAnimation([](){});
    }
    
//    runAnimation->setDelayPerUnit(GameData::getInstance()->defaultDelayPerUnit);
//    Animate *animate = Animate::create(runAnimation);
//    _actionSprite->stopAllActions();
//    _actionSprite->runAction(RepeatForever::create(animate));
}

void Monster::attack(Person *attackTarget){
    
}

void Monster::die(){
    
}

void Monster::loseBlood(int loseBloodValue){
    if (loseBloodValue < 0){
        CCLOG("怎么还掉负血啊？检查一下 %d", loseBloodValue);
        return;
    }
//    CCLOG("%s %d", __func__, _hp);
    if (loseBloodValue > _hp){
        _hp = 0;
        _lifeBar->updateLife(0);
    }else {
        _hp = _hp - loseBloodValue;
        _lifeBar->updateLife(_hp);
    }
}

void Monster::addBlood(int addBloodValue){
    if (addBloodValue < 0){
        CCLOG("怎么还加负血啊？检查一下 %d", addBloodValue);
        return;
    }
    //TODO:是否允许加到比出生还要多的血？现在是允许，有一个问题，lifeBar 会加超出界
    
    _hp = _hp + addBloodValue;
    _lifeBar->updateLife(_hp);
}

void Monster::update(float dt){
//    Vec2 currentPosition = this->getPosition();
//    CCLOG("(%.2f, %.2f)", currentPosition.x, currentPosition.y);
    this->setLocalZOrder(getBattleLocalZOrderByActor(this));
}

#pragma mark - Protected Method

void Monster::_initMonsterData(){
    _side = "monster";
    _myMonsterData = GameData::getInstance()->getMonsterDataByMonsterName(_name);
//    printMonsterData(_myMonsterData);
//    _runSpeed = _myMonsterData.speed; //TODO: speed 是一个字符串描述
    _runSpeed = 30;
}

void Monster::_initAnimationData(){
    //MARK:AnimationData 暂时不用，在 _initMonsterActor 临时创建出来传给 Actor
}

void Monster::_initMonsterActor(){
    PersonActorAnimatoinData animationData;
    animationData.numberOfAttackAnimationFrame = _myMonsterData.attackFrameNumber;
    animationData.numberOfBackwardAnimationFrame = _myMonsterData.runBackwardFrameNumber;
    animationData.numberOfDieAnimationFrame = _myMonsterData.dieFrameNumber;
    animationData.numberOfForwardAnimationFrame = _myMonsterData.runForwardFrameNumber;
    animationData.numberOfTowardAniamtionFrame = _myMonsterData.runTowardFrameNumber;
    animationData.numberOfRemoteAttackAnimationFrame = _myMonsterData.attackRemoteFrameNumber;
    animationData.numberOfReleaseSkillAnimationFrame = _myMonsterData.releaseSkillFrameNumber;
    
    _personActor = PersonActor::createPersonActorByName("monster", _name, animationData);
    _personActor->setScale(1.5, 1.5);
    _personActor->setAnchorPoint(Vec2(0.5, 0.2));
    this->addChild(_personActor);
}

void Monster::_initLifeBar(){
    Size actorSize = _personActor->getContentSize();
//    CCLOG("ActorSize: (%f, %f)", actorSize.width, actorSize.height);
    //TODO:根据 Monster 来选择血条的尺寸
    _lifeBar = BattleLifeBarSprite::createBattleLifeBarSprite(battle_life_bar_small, _myMonsterData.healthPoint);
    Size lifeBarSize = _lifeBar->getContentSize();
    _lifeBar->setAnchorPoint(Vec2(0.5, 0));
    _lifeBar->setPosition(lifeBarSize.width / 2, actorSize.height + 10);
    this->addChild(_lifeBar, 100);
}

void Monster::_initBattleMapData(){
    
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

void Monster::_testCode(){
    this->schedule([&](float dt){
        if (CCRANDOM_0_1() > 0.5){
            this->loseBlood(10);
        }
    }, 1, "Test");
}













