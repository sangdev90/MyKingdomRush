//
//  Archer.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/25.
//
//

#include "Archer.hpp"
#include "ToolFunction.hpp"
#include "GameData.hpp"
#include "TowerShootThing.hpp"

USING_NS_CC;

Archer *Archer::createArcher(){

    Archer *newArcher = new (std::nothrow) Archer();
    if (newArcher && newArcher->initArcher()){
        newArcher->autorelease();
        return newArcher;
    }
    
    delete newArcher;
    newArcher = nullptr;
    return nullptr;
    
}

bool Archer::initArcher(){
    if (!this->initWithSpriteFrameName(getTowerShooterSpriteFrameNameByNameAndLevel(_name, _level))){
        return false;
    }
    
    TowerShooterData myTowerShooterData = GameData::getInstance()->getTowerShooterDataByNameAndLevel(_name, _level);
    
    for (int index = 0; index < myTowerShooterData.preAttackUpFrameNumber; ++index){
        std::string frameName = getTowerShooterAttackFrameNameByNameAndLevelAndDistanceAndNumber(_name, _level, "up", index);
        _attackUpSpriteFrameArray.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
    }
    
    for (int index = 0; index < myTowerShooterData.preAttackDownFrameNumber; ++index){
        std::string frameName = getTowerShooterAttackFrameNameByNameAndLevelAndDistanceAndNumber(_name, _level, "down", index);
        _attackDownSpriteFrameArray.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
    }
    
    return true;
}

void Archer::attack(const cocos2d::Vec2 &from, const cocos2d::Vec2 &to, const std::function<void ()> &attackCallback){
    
    Animation *attackDownAnimation = Animation::createWithSpriteFrames(_attackDownSpriteFrameArray);
    attackDownAnimation->setDelayPerUnit(GameData::getInstance()->defaultDelayPerUnit);
    Animate *attackDownAnimate = Animate::create(attackDownAnimation);
    
    Animation *attackUpAnimation = Animation::createWithSpriteFrames(_attackUpSpriteFrameArray);
    attackUpAnimation->setDelayPerUnit(GameData::getInstance()->defaultDelayPerUnit);
    Animate *attackUpAnimate = Animate::create(attackUpAnimation);
    
    if (from.x > to.x){
        this->setScale(-1, 1);
        if (from.y > to.y){
            //Down
            
            this->runAction(Sequence::create(attackDownAnimate,
                                             CallFuncN::create([attackCallback](Node *target){
                                                attackCallback();
                                                target->stopAllActions();
                                             }),
                                             NULL));
            
        }else {
            //Up
            
            this->runAction(Sequence::create(attackUpAnimate,
                                             CallFuncN::create([attackCallback](Node *target){
                                                attackCallback();
                                                target->stopAllActions();
                                             }),
                                             NULL));
            
        }
    }else {
        this->setScale(1, 1);
        if (from.y > to.y){
            //Down
            
            this->runAction(Sequence::create(attackDownAnimate,
                                             CallFuncN::create([attackCallback](Node *target){
                                                attackCallback();
                                                target->stopAllActions();
                                             }),
                                             NULL));
            
        }else {
            //Up
            
            this->runAction(Sequence::create(attackUpAnimate,
                                             CallFuncN::create([&, attackCallback, from, to](Node *target){
                                                TowerShootThing *arrow = TowerShootThing::createTowerShootThingByNameAndLevel(GameData::getInstance()->towerShootThingName.arrow, _level);
                                                arrow->setPosition(from);
                                                this->addChild(arrow);
                                                arrow->attack(from, to, attackCallback);
//                                                attackCallback();
                                                target->stopAllActions();
                                             }),
                                             NULL));
            
        }
    }
    
//    CCLOG("I'm a %s, now I attack!", _name.c_str());
    attackCallback();
}

void Archer::updateTowerShooterLevel(const std::string &level){
    TowerShooter::updateTowerShooterLevel(level);
    
}


