//
//  Tower.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/21.
//
//

#include "Tower.hpp"
#include "GameData.hpp"
#include "ToolFunction.hpp"

#include "ArcherTower.hpp"
#include "DefenceTower.hpp"
#include "MageTower.hpp"
#include "ArtilleryTower.hpp"
#include "BattleLayer.hpp"
#include "Monster.hpp"

USING_NS_CC;

#pragma mark - Static Method

Tower *Tower::createTowerByName(const std::string &name, BattleLayer *battleLayer){
    
    if (name == GameData::getInstance()->towerName.archerTower){
        Tower *archerTower = ArcherTower::createArcherTower();
        archerTower->setBattleLayerPointer(battleLayer);
        return archerTower;
    }
    
    if (name == GameData::getInstance()->towerName.defenceTower){
        
    }
    
    if (name == GameData::getInstance()->towerName.mageTower){
        
    }
    
    if (name == GameData::getInstance()->towerName.artilleryTower){
        
    }
    
    CCLOG("要创建一个不知名的 Tower : %s ", name.c_str());
    return nullptr;
    
}

#pragma mark - Member Method

void Tower::changeLevel(const std::string &levelTag){
    
    if (_level == "level1"){
        _level = "level2";
        this->updateTowerData();
        return;
    }else if (_level == "level2"){
        _level = "level3";
        this->updateTowerData();
        return;
    }else{
        if (levelTag == "level41" || levelTag == "level42"){
            _level = levelTag;
            this->updateTowerData();
            return;
        }else {
            CCLOG("I Don't Know Chang My Level To What!!!!!!!!!!!!!!!");
            return;
        }
    }
}

void Tower::updateTowerData(){
    this->updateLevel();
}

bool Tower::isMonsterCanAttack(Monster *monster){
    if (monster == nullptr){
        CCLOG("Monster is null");
    }
    Vec2 monsterPosition = monster->getPosition();
    Vec2 towerPosition   = this->getPosition();
    float distanceWithMonster = distanceBetweenTwoVec2WithoutSqrt(towerPosition, monsterPosition);
    
    float sinAlpha = (monsterPosition.y - towerPosition.y) / distanceWithMonster;
    float cosAlpha = (monsterPosition.x - towerPosition.x) / distanceWithMonster;
    
    float attackDistance = (_attackScopeData.longAxis * cosAlpha) * (_attackScopeData.longAxis * cosAlpha) + (_attackScopeData.shortAxis * sinAlpha) * (_attackScopeData.shortAxis * sinAlpha); //反正都是比较大小，这里就不开方了
    
    if (attackDistance > distanceWithMonster){
        return true;
    }else {
        return false;
    }
}

#pragma mark - Impure Virtual Method

void Tower::updateLevel(){
    
}

bool Tower::initTower(){
    if (!Sprite::init()){
        return false;
    }
    this->initAttackScopeData();
    
    return true;
}

Monster *Tower::findAttackTarget(){
    
    if (_attackTarget){
        if (!_attackTarget->isDie){
            if (this->isMonsterCanAttack(_attackTarget)){
                CCLOG("");
                return _attackTarget;
            }
        }
    }
    
    return nullptr;
    
    //要是已经有目标而且这个目标没死并且还在我的攻击范围内，那就接着打他，不换人
    if (_attackTarget && !_attackTarget->isDie && this->isMonsterCanAttack(_attackTarget)){
        return _attackTarget;
    }
    
    //没有攻击目标了，那再找一个
    for (Monster *monster : _battleLayerPointer->monsterArray){
        if (this->isMonsterCanAttack(monster)){
            CCLOG("我找到我要打的人了！");
//            _attackTarget = monster;
            return monster;
        }
        
    }
    
    //没找着攻击目标，歇着
    return nullptr;
    
}

void Tower::onEnter(){
    Sprite::onEnter();
}

void Tower::onExit(){
    
}

#pragma mark - Pure Virtual Method

Tower::~Tower(){
    
}
