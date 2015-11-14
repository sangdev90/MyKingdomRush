//
//  Monster.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/14.
//
//

#include "Monster.hpp"
#include "GameData.hpp"

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

void Monster::initMonsterData(){
    _side = "monster";
    
}

void Monster::initAnimationData(){
    
}