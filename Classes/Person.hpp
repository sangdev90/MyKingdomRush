//
//  Person.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/11.
//
//

#ifndef Person_hpp
#define Person_hpp

#include <stdio.h>
#include "cocos2d.h"

class Person : public cocos2d::Sprite{
public:
    
    Person(const std::string &name):
    _name(name) {};
    
#pragma mark - Static Method
    
    static Person *createMonsterByName(const std::string &name, const std::vector<cocos2d::Vec2> &path);
    static Person *createSoldierByName(const std::string &name);
    
#pragma mark - Pure Virtual Method
    
    virtual void run() = 0;
    virtual void attack(Person *attackTarget) = 0;
    virtual void die() = 0;
    
#pragma mark - Impure Virtual Method
    
#pragma mark - Public Data Member
    
    bool isDie = false;
    
protected:
    
    cocos2d::Sprite *_actionSprite;
    
    std::string _name;  //for example : desertThug
    std::string _side;  //for example : monster || soldier
    std::string _info;  //
    
    int _hp = 100;
    int _runSpeed = 10;
    int _attackRange = 50;
    
    
    //MARK: Up is I want, Down is to be change
    
    int _numberOfAttackAnimationFrame;
    cocos2d::Vector<cocos2d::SpriteFrame *> _attackAniamtionFrameArray;
    int _numberOfDieAnimationFrame;
    cocos2d::Vector<cocos2d::SpriteFrame*> _dieAnimationFrameArray;
    int _numberOfForwardAnimationFrame;
    cocos2d::Vector<cocos2d::SpriteFrame *> _runForwardAnimationFrameArray;
    int _numberOfBackwardAnimationFrame;
    cocos2d::Vector<cocos2d::SpriteFrame *> _runBackwardAnimationFrameArray;
    int _numberOfTowardAnimationFrame;
    cocos2d::Vector<cocos2d::SpriteFrame *> _runTowardAnimationFrameArray;
    
    
};

#endif /* Person_hpp */
