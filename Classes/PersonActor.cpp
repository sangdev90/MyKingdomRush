//
//  PersonActor.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/29.
//
//

#include "PersonActor.hpp"
#include "GameData.hpp"
#include "MonsterActor.hpp"

PersonActor *PersonActor::createPersonActorByName(const std::string &side, const std::string &name, const PersonActorAnimatoinData &animationData){
    
    if (side == "monster"){
        PersonActor *personActor = MonsterActor::createMonsterActorByName(name, animationData);
        return personActor;
    }else if (side == "soldier"){
        
    }else {
        CCLOG("创建 PersonActor side: %s 无法创建", side.c_str());
    }
    
    return nullptr;
}

bool PersonActor::initWithAnimationData(const PersonActorAnimatoinData &animationData){
    
    if (Sprite::initWithSpriteFrameName(_getPerosonActorNormalSpriteName())){
        _numberOfAttackAnimationFrame = animationData.numberOfAttackAnimationFrame;
        _numberOfDieAnimationFrame = animationData.numberOfDieAnimationFrame;
        _numberOfForwardAnimationFrame = animationData.numberOfForwardAnimationFrame;
        _numberOfBackwardAnimationFrame = animationData.numberOfBackwardAnimationFrame;
        _numberOfTowardAnimationFrame = animationData.numberOfTowardAniamtionFrame;
        
        prepareAnimation(_attackAniamtionFrameArray, "attack", _numberOfAttackAnimationFrame);
        prepareAnimation(_dieAnimationFrameArray, "die", _numberOfDieAnimationFrame);
        prepareAnimation(_runForwardAnimationFrameArray, "forward", _numberOfForwardAnimationFrame);
        prepareAnimation(_runBackwardAnimationFrameArray, "backward", _numberOfBackwardAnimationFrame);
        prepareAnimation(_runTowardAnimationFrameArray, "toward", _numberOfTowardAnimationFrame);
        
        _defaultDelayPerUnit = GameData::getInstance()->defaultDelayPerUnit;
        
        return true;
        
    }
    
    return false;
}

void PersonActor::playAttackAnimation(const std::function<void ()> &callback){
    _state = "attack";
    _playAnimation(_attackAniamtionFrameArray, callback);
}

void PersonActor::playBackwardAnimation(const std::function<void ()> &callback){
    _state = "backward";
    _playAnimation(_runBackwardAnimationFrameArray, callback);
}

void PersonActor::playDieAnimation(const std::function<void ()> &callback){
    _state = "die";
    _playAnimation(_dieAnimationFrameArray, callback);
}

void PersonActor::playForwardAnimation(const std::function<void ()> &callback){
    _state = "forward";
    _playAnimation(_runForwardAnimationFrameArray, callback);
}

void PersonActor::playTowardAnimation(const std::function<void ()> &callback){
    _state = "toward";
    _playAnimation(_runTowardAnimationFrameArray, callback);
}

PersonActor::~PersonActor(){
    
}
